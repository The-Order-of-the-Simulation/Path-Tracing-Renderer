#include <iostream>
using namespace std;

#include <thread>
#include <fstream>

// Include Common Header
#include "common.hpp"

// ##### Parameters #####

// Image Resolution
#define IMAGE_SIZE_X 320
#define IMAGE_SIZE_Y 240

// Samples per Pixel
#define SPP 512

// Maximum Light Bounces
#define MAX_BOUNCES 16

// Tonemap Exposure
#define TONEMAP_EXPOSURE 1.0F

// Camera Field of View
#define CAMERA_FOV 1.0F

// ##### Rendering #####

inline vec3 skyColor(vec3 rd)
{
	// Light Source
	if(dot3(float3(0.0F, 1.0F, 0.0F), rd) > 0.8F)
	{
		return float3f(10.0F);
	}

	return float3f(0.8F*max(dot3(float3(0.0F, 1.0F, 0.0F), rd), 0.0F)+0.2F);
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

inline intersection trace(vec3 ro, vec3 rd)
{
	intersection t;
	t.hit = false;

	uint32_t seed = 1U;

	for(int i = 0; i < 8; i++)
	{
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = multiply_vec3f(subtract_vec3f(spherePosition, 0.5F), 2.0F);

		intersection t0 = sphere(ro, rd, spherePosition, 0.5F);
		t = process_hit(t, t0);
	}

	return t;
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
		attenuation = multiply_vec3(attenuation, float3f(0.8F));
		rd = normalize3(nrand3(0.5F, t.normal));
	}

	// Sample Expired
	return float3f(-1.0F);
}

void render()
{
	vec3 imageBuffer[IMAGE_SIZE_X*IMAGE_SIZE_Y];

	for(int x = 0; x < IMAGE_SIZE_X; x++) {
	for(int y = 0; y < IMAGE_SIZE_Y; y++) {
		vec3 pixelColor = float3f(0.0F);
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
				pixelColor = add_vec3(pixelColor, color);
				accumulation++;
			}
		}

		pixelColor = accumulation != 0 ? divide_vec3f(pixelColor, float(accumulation)) : float3f(0.0F);

		// HDR Exposure Tonemap
		pixelColor = tonemap(pixelColor, TONEMAP_EXPOSURE);

		imageBuffer[x+(y*IMAGE_SIZE_X)] = pixelColor;
	}
	}

	std::cout << "Saving render to render.ppm..." << std::endl;

	ofstream imageFile;
	imageFile.open("render.ppm");

	// Write Header to File
	imageFile << "P3" << std::endl << IMAGE_SIZE_X << " " << IMAGE_SIZE_Y << std::endl << "65535" << std::endl;

	// Write Pixels to File
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
}

int main()
{
	// Detect Number of Hardware Threads
	int n_threads = thread::hardware_concurrency();

	if(n_threads < 1)
	{
		std::cout << "Critical Error: hardware_concurrency reports " << n_threads << " threads!" << std::endl;
		std::cout << "Please make sure your system supports std::thread. Exiting..." << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "This machine reports having " << n_threads << " hardware threads" << std::endl;

	std::cout << "Starting Render..." << std::endl;

	thread thread0(render);

	thread0.join();

	std::cout << "Done!" << std::endl;

	// Return the Exit Code
	return EXIT_SUCCESS;
}