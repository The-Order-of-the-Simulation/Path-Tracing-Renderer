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
	vec3 rayPos = ro, rayDir = rd, attenuation = vec3(1.0F);
	intersection t;
	
	for(int i = 0; i < MAX_BOUNCES; i++)
	{
		t = trace(rayPos, rayDir);

		if(!t.hit) return (skyColor(rayDir) * attenuation);

		/*
		if(t.materialProperties.volume)
		{
			rayPos = add_vec3(rayPos, multiply_vec3f(rd, t.tMin));
			attenuation = multiply_vec3(attenuation, t.materialProperties.baseColor);
			rd = normalize3(nrand3(t.materialProperties.anisotropy, rd));
		}
		else
		{
			rayPos = add_vec3(rayPos, multiply_vec3f(rd, t.tMin-0.0001F));
			attenuation = multiply_vec3(attenuation, t.materialProperties.baseColor);
			rd = normalize3(reflect3(rd, normalize3(nrand3(t.materialProperties.roughness, t.normal))));
		}
		*/

		rayPos = rayPos + (rayDir * t.tMin - 0.0001F);
		attenuation = attenuation * vec3(0.600F, 0.700F, 0.800F);

		rayDir = normalize(reflect(rayDir, normalize(nrand3(0.5F, t.normal))));
	}

	// Sample Expired
	return vec3(-1.0F);
}

vec3 imageBuffer[IMAGE_SIZE_X * IMAGE_SIZE_Y];

void renderImage(vec3 *imageBuffer, int minx, int maxx, int miny, int maxy) {
	int accumulation;
	vec3 *pixelColor;

	#pragma omp parallel for
	for(int x = minx; x < maxx; x++) 
	{
		for(int y = miny; y < maxy; y++) 
		{
			pixelColor = &imageBuffer[x+(y*IMAGE_SIZE_X)];
			accumulation = 0;

			// Initialize Random Number Generator
			ns = uint32_t(x+(y*IMAGE_SIZE_X)+1);

			for(int i = 0; i < SPP; i++)
			{
				vec2 uv = ((pixelFilter(vec2(x, y)) - (vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y) * 0.5F)) / max(IMAGE_SIZE_X, IMAGE_SIZE_Y)) * 2.0F;

				vec3 ro = vec3(0.0F, 0.0F, 2.0F);

				// -uv.y because .ppm format reads inverted y
				vec3 rd = normalize(vec3(CAMERA_FOV*uv.x, CAMERA_FOV*-uv.y, -1.0F));

				vec3 color = radiance(ro, rd);

				bool expired = color.x < 0.0F || color.y < 0.0F || color.z < 0.0F;

				if(!expired) {
					*pixelColor = *pixelColor + color;
					accumulation++;
				}
			}

			// Calculate the Accumulated Radiance
			*pixelColor = accumulation != 0 ? (*pixelColor / float(accumulation)) : vec3(0.0F);

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
	if(n_threads < 1) {
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

	// Start Execution Timer
	auto start = chrono::high_resolution_clock::now();



	//renderImage(imageBuffer, 0, IMAGE_SIZE_X, 0, IMAGE_SIZE_Y);
	thread t1(renderImage, imageBuffer, 0, IMAGE_SIZE_X / 2, 0, IMAGE_SIZE_Y / 2);
	thread t2(renderImage, imageBuffer, IMAGE_SIZE_X / 2, IMAGE_SIZE_X, 0, IMAGE_SIZE_Y / 2);
	thread t3(renderImage, imageBuffer, 0, IMAGE_SIZE_X / 2, IMAGE_SIZE_Y / 2, IMAGE_SIZE_Y);
	thread t4(renderImage, imageBuffer, IMAGE_SIZE_X / 2, IMAGE_SIZE_X, IMAGE_SIZE_Y / 2, IMAGE_SIZE_Y);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

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

	std::cout << "Done!" << std::endl;

	// Return the Exit Code
	return EXIT_SUCCESS;
}