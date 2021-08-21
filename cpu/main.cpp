#include <iostream>
using namespace std;

#include <chrono>
#include <cmath>
#include <thread>
#include <fstream>

// Include Common Header
#include "common.hpp"

// Include Config Header
#include "config.hpp"

// ##### Rendering #####

inline vec3 skyColor(vec3 rd)
{
	// Light Source
	if(dot3(float3(0.0F, 1.0F, 0.0F), rd) > 0.8F)
	{
		return float3(2.0F, 10.0F, 2.0F);
	}

	float x = max(dot3(float3(0.0F, 1.0F, 0.0F), rd), 0.0F)+(max(dot3(float3(0.0F, -1.0F, 0.0F), rd), 0.0F)*0.05F);

	return float3f(0.8F*x+0.2F);
}

intersection process_hit(intersection t0, intersection t1)
{
	// If neither intersection hit, this function will return t0

	if(t1.hit)
	{
		if(t0.hit)
		{
			intersection t;
			t.tMin = min(t0.tMin, t1.tMin);
			t.tMax = max(t0.tMax, t1.tMax);
			t.hit = true;
			t.normal = t0.tMin < t1.tMin ? t0.normal : t1.normal;

			return t;
		}

		return t1;
	}

	return t0;
}

/*
inline intersection trace(vec3 ro, vec3 rd)
{
	intersection t;
	t.hit = false;

	uint32_t seed = 1U;

	for(int i = 0; i < 8; i++)
	{
		// Calculate Sphere Position
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = multiply_vec3f(subtract_vec3f(spherePosition, 0.5F), 2.0F);

		// Calculate Intersection
		intersection t0 = sphere(ro, rd, spherePosition, 0.5F);
		t = process_hit(t, t0);
	}

	return t;
}
*/

inline float DE(vec3 pos)
{
	float minDist = 1000.0F;

	uint32_t seed = 1U;

	for(int i = 0; i < 8; i++)
	{
		// Calculate Sphere Position
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = multiply_vec3f(subtract_vec3f(spherePosition, 0.5F), 2.0F);
		spherePosition = subtract_vec3(pos, spherePosition);
		minDist = min(minDist, dot3(spherePosition, spherePosition));
	}

	return sqrtf(minDist)-0.5F;
}

#define hitDist 0.0001F

inline vec3 sampleNormal(vec3 pos)
{
	const vec2 k = float2(-1.0F, 1.0F);
	return normalize3(add_vec3(add_vec3(add_vec3(
	multiply_vec3f(float3(k.x, k.x, k.x), DE(add_vec3(pos, multiply_vec3f(float3(k.x, k.x, k.x), hitDist)))),
	multiply_vec3f(float3(k.x, k.y, k.y), DE(add_vec3(pos, multiply_vec3f(float3(k.x, k.y, k.y), hitDist))))),
	multiply_vec3f(float3(k.y, k.x, k.y), DE(add_vec3(pos, multiply_vec3f(float3(k.y, k.x, k.y), hitDist))))),
	multiply_vec3f(float3(k.y, k.y, k.x), DE(add_vec3(pos, multiply_vec3f(float3(k.y, k.y, k.x), hitDist))))));
}

inline intersection trace(vec3 ro, vec3 rd)
{
	intersection outInt;
	outInt.tMin = -1.0F;
	outInt.tMax = -1.0F;
	outInt.hit = false;

	float t = 0.0F;

	for(int i = 0; i < 128; i++)
	{
		if(t > 32.0F)
		{
			break;
		}

		float td = DE(add_vec3(ro, multiply_vec3f(rd, t)));

		if(td < hitDist)
		{
			outInt.tMin = t;
			outInt.hit = true;
			outInt.normal = sampleNormal(add_vec3(ro, multiply_vec3f(rd, t)));
			return outInt;
		}

		t += td;
	}

	return outInt;
}

inline vec3 radiance(vec3 ro, vec3 rd)
{
	vec3 rayPos = ro, attenuation = float3f(1.0F);

	for(int i = 0; i < MAX_BOUNCES; i++)
	{
		intersection t = trace(rayPos, rd);

		if(!t.hit)
		{
			return multiply_vec3(skyColor(rd), attenuation);
		}

		rayPos = add_vec3(rayPos, multiply_vec3f(rd, t.tMin-0.001F));
		attenuation = multiply_vec3(attenuation, float3(0.200F, 0.200F, 0.800F));
		rd = normalize3(reflect3(rd, normalize3(nrand3(0.5F, t.normal))));
	}

	// Sample Expired
	return float3f(-1.0F);
}

void renderImage(vec3 *imageBuffer)
{
	#pragma omp parallel for
	for(int x = 0; x < IMAGE_SIZE_X; x++) {
	for(int y = 0; y < IMAGE_SIZE_Y; y++) {
		vec3 *pixelColor = &imageBuffer[x+(y*IMAGE_SIZE_X)];
		int accumulation = 0;

		// Initialize Random Number Generator
		ns = uint32_t(x+(y*IMAGE_SIZE_X)+1);

		for(int i = 0; i < SPP; i++)
		{
			vec2 uv = multiply_vec2f(divide_vec2f(subtract_vec2(pixelFilter(float2(x, y)), multiply_vec2f(float2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0.5F)), max(IMAGE_SIZE_X, IMAGE_SIZE_Y)), 2.0F);

			const vec3 ro = float3(0.0F, 0.0F, 2.0F);

			// -uv.y because .ppm format reads inverted y
			vec3 rd = normalize3(float3(CAMERA_FOV*uv.x, CAMERA_FOV*-uv.y, -1.0F));

			vec3 color = radiance(ro, rd);

			bool expired = color.x < 0.0F || color.y < 0.0F || color.z < 0.0F;

			if(!expired)
			{
				*pixelColor = add_vec3(*pixelColor, color);
				accumulation++;
			}
		}

		// Calculate the Accumulated Radiance
		*pixelColor = accumulation != 0 ? divide_vec3f(*pixelColor, float(accumulation)) : float3f(0.0F);

		// HDR Exposure Tonemap
		*pixelColor = tonemap(*pixelColor, TONEMAP_EXPOSURE);
	}
	}
}

int main()
{
	// Detect Number of Hardware Threads
	int n_threads = thread::hardware_concurrency();

	// Check if hardware_concurrency reported garbage
	if(n_threads < 1)
	{
		std::cout << "Critical Error: hardware_concurrency reports " << n_threads << " threads!" << std::endl;
		std::cout << "Please make sure your system supports std::thread. Exiting..." << std::endl;

		// Return the Exit Code
		return EXIT_FAILURE;
	}

	// Output Multithreading Info
	std::cout << "This machine reports having " << n_threads << " hardware threads" << std::endl << std::endl;

	// Output Render Parameters
	std::cout << "Render Resolution: " << IMAGE_SIZE_X << "x" << IMAGE_SIZE_Y << std::endl;
	std::cout << "Render Samples: " << SPP << std::endl;
	std::cout << "Render Light Bounces: " << MAX_BOUNCES << std::endl;
	std::cout << "Tonemap Exposure: " << TONEMAP_EXPOSURE << std::endl;
	std::cout << "Camera FOV: " << CAMERA_FOV << std::endl << std::endl;

	std::cout << "Starting Render..." << std::endl;

	// Allocate Image Buffer
	vec3 *imageBuffer;
	imageBuffer = (vec3*)malloc(sizeof(vec3)*IMAGE_SIZE_X*IMAGE_SIZE_Y);

	// Start Execution Timer
	auto start = chrono::high_resolution_clock::now();

	renderImage(imageBuffer);

	//thread thread0(renderImage, imageBuffer);
	//thread0.join();

	// Stop Execution Timer
	auto stop = chrono::high_resolution_clock::now();

	std::cout << "Image rendered in " << (double)chrono::duration_cast<chrono::nanoseconds>(stop-start).count()/1000000.0 << " Milliseconds!" << std::endl << std::endl;
	std::cout << "Writing image to disk..." << std::endl;

	// Start Execution Timer
	start = chrono::high_resolution_clock::now();

	ofstream imageFile;
	imageFile.open("render.ppm");

	// Write Header to File
	imageFile << "P3" << std::endl << IMAGE_SIZE_X << " " << IMAGE_SIZE_Y << std::endl << "65535" << std::endl;

	for(int i = 0; i < IMAGE_SIZE_X*IMAGE_SIZE_Y; i++)
	{
		// Quantization
		int channel_r = min(max(int(65535.0F*imageBuffer[i].x), 0), 65535);
		int channel_g = min(max(int(65535.0F*imageBuffer[i].y), 0), 65535);
		int channel_b = min(max(int(65535.0F*imageBuffer[i].z), 0), 65535);

		imageFile << channel_r << " " << channel_g << " " << channel_b << " ";
	}

	imageFile << "# Rendered with OpenPT";
	imageFile.close();

	// Stop Execution Timer
	stop = chrono::high_resolution_clock::now();

	std::cout << "Render was saved as render.ppm in " << (double)chrono::duration_cast<chrono::nanoseconds>(stop-start).count()/1000000.0 << " Milliseconds!" << std::endl << std::endl;

	free(imageBuffer);

	std::cout << "Done!" << std::endl;

	// Return the Exit Code
	return EXIT_SUCCESS;
}