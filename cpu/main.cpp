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

// Include Scene Header
#include "scene.hpp"

vec3 radiance(vec3 ro, vec3 rd)
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
		attenuation = multiply_vec3(attenuation, float3(0.200F, 0.400F, 0.800F));
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