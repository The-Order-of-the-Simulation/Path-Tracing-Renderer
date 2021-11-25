#include <iostream>

#include <common.hpp>

// Blackman-Harris Pixel Filter
vec2 pixel_filter(vec2 pixel_coord)
{
	// https://en.wikipedia.org/wiki/Window_function#Blackman–Harris_window
	// w[n] = a0 - a1 * cos(2 * pi * n / N) + a2 * cos(4 * pi * n / N) - a3 * cos(6 * pi * n / N)
	// a0 = 0.35875; a1 = 0.48829; a2 = 0.14128; a3 = 0.01168;

	const float a0 = 0.35875f;
	const float a1 = 0.48829f;
	const float a2 = 0.14128f;
	const float a3 = 0.01168f;

	//float n = 0.5f * random_float() + 0.5f;
	float n = random_float();

	float w = a0 - a1 * glm::cos(2.0f * pi * n) + a2 * glm::cos(4.0f * pi * n) - a3 * glm::cos(6.0f * pi * n);

	return pixel_coord + (2.0f * udir2() * w);
}

// https://www.iquilezles.org/www/articles/cputiles/cputiles.htm

void render_image(image_buffer render_buffer)
{
	// Initialize Random Number Generator
	init_rng(1);

	vec2 resolution = vec2(render_buffer.size_x, render_buffer.size_y);

	for(unsigned int pixel_coord_x = 0; pixel_coord_x < render_buffer.size_x; pixel_coord_x++) {
	for(unsigned int pixel_coord_y = 0; pixel_coord_y < render_buffer.size_y; pixel_coord_y++) {
		vec3 color = vec3(0);
		unsigned int samples = 0;

		for(unsigned int i = 0; i < MAX_SAMPLES; i++)
		{
			//init_rng(i);

			vec2 uv = 2.0f * ( ( pixel_filter( vec2(pixel_coord_x, pixel_coord_y) ) - ( 0.5f * vec2(resolution) ) ) / glm::max(resolution.x, resolution.y) );

			vec3 ro = vec3(0.0f, 0.0f, 4.0f);
			vec3 rd = normalize( vec3(CAMERA_FOV * uv, -1) );

			vec3 c = radiance(ro, rd);

			bool sample_expired = c.r < 0.0f || c.g < 0.0f || c.b < 0.0f;
			bool sample_invalid = isinff(c.r) || isinff(c.g) || isinff(c.b) || isnanf(c.r) || isnanf(c.g) || isnanf(c.b);

			// Check if the sample was discarded and accumulate
			if(!sample_expired && !sample_invalid)
			{
				color += c;

				samples++;
			}
		}

		color = samples != 0 ? color / float(samples) : color;

		#ifdef HDR
		render_buffer.buffer[pixel_coord_x + (pixel_coord_y * render_buffer.size_x)] = color;
		#else
		color = clamp(1.0f - glm::exp(-glm::max(color, 0.0f) * EXPOSURE), 0.0f, 1.0f);
		render_buffer.buffer[pixel_coord_x + ( ( (render_buffer.size_y - 1) - pixel_coord_y ) * render_buffer.size_x )] = color;
		#endif
	}
	}
}

// ##### Main #####
int main()
{
	const unsigned int RENDER_SIZE_X = 640;
	const unsigned int RENDER_SIZE_Y = 480;

	std::cout << "Initializing..." << std::endl;

	image_buffer render_buffer;

	render_buffer.allocate(RENDER_SIZE_X, RENDER_SIZE_Y);

	std::cout << "Starting Render..." << std::endl;

	render_image(render_buffer);

	std::cout << "Writing Render to Disk..." << std::endl;

	#ifdef HDR
	write_render_HDR(render_buffer);
	#else
	write_render(render_buffer);
	#endif

	std::cout << "Cleaning Up..." << std::endl;

	render_buffer.cleanup();

	std::cout << "Done!" << std::endl;

	return EXIT_SUCCESS;
}