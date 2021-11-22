#include <iostream>

#include "common.hpp"

// ##### Path-Tracing #####

vec3 ortho(vec3 v)
{
	return normalize( glm::abs(v.x) > glm::abs(v.z) ? vec3(-v.y, v.x, 0.0f) : vec3(0.0f, -v.z, v.y) );
}

// Weighted Cosine Sampling
vec3 cosine_weighted_sample()
{
	vec2 z = rand2();
	vec2 r = vec2( 2.0f * pi * z.x, glm::sqrt(z.y) );
	return vec3( r.y * vec2( glm::cos(r.x), glm::sin(r.x) ), glm::sqrt(1.0f - r.y * r.y) );
}

// Lambertian Probability Distribution Function
float PDF(vec3 wi, vec3 wo)
{
	return glm::max(wi.z, 0.000001f) * inverse_pi;
}

// Lambertian Bidirectional Reflectance Distribution Function
vec3 BRDF(vec3 wi, vec3 wo)
{
	return vec3(0.8f) * inverse_pi;
}

vec3 radiance(vec3 ro, vec3 rd)
{
	vec3 rayPos = ro;
	vec3 rayDir = rd;

	vec3 attenuation = vec3(1);

	for(unsigned int bounces = 0; bounces < MAX_BOUNCES; bounces++)
	{
		raycast raycast_data = trace(rayPos, rayDir);

		if(raycast_data.expire)
		{
			break;
		}

		if(!raycast_data.hit)
		{
			return sky_radiance(rayDir) * attenuation;
		}

		rayPos += rayDir * (raycast_data.tMin - HIT_DIST);

		vec3 t = ortho(raycast_data.normal);
		vec3 b = cross(t, raycast_data.normal);
		mat3 surf2world = mat3(t, b, raycast_data.normal);
		mat3 world2surf = transpose(surf2world);

		vec3 wi = cosine_weighted_sample();
		vec3 wo = world2surf * -rayDir;

		// loicvdb's magic wisdom go brrr
		attenuation *= BRDF(wi, wo) / PDF(wi, wo) * glm::max(wi.z, 0.0f);

		rayDir = surf2world * wi;
	}

	return vec3(-1);
}

// Blackman-Harris Pixel Filter
vec2 pixel_filter(vec2 pixel_coord)
{
	// https://en.wikipedia.org/wiki/Window_function#Blackman–Harris_window
	// w[n] = a0-a1*cos(2*pi*n/N)+a2*cos(4*pi*n/N)-a3*cos(6*pi*n/N)
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

// ##### Main #####
int main()
{
	const unsigned int RENDER_SIZE_X = 640;
	const unsigned int RENDER_SIZE_Y = 480;
	const vec2 resolution = vec2(RENDER_SIZE_X, RENDER_SIZE_Y);

	std::cout << "Initializing..." << std::endl;

	image_buffer render_buffer;

	render_buffer.allocate(RENDER_SIZE_X, RENDER_SIZE_Y);

	std::cout << "Starting Render..." << std::endl;

	uvec2 pixel_coord;
	for(pixel_coord.x = 0; pixel_coord.x < RENDER_SIZE_X; pixel_coord.x++) {
	for(pixel_coord.y = 0; pixel_coord.y < RENDER_SIZE_Y; pixel_coord.y++) {
		vec3 color = vec3(0);
		unsigned int samples = 0;
		for(unsigned int i = 0; i < MAX_SAMPLES; i++)
		{
			init_rng( (i)*(RENDER_SIZE_X*RENDER_SIZE_Y)+(pixel_coord.x + pixel_coord.y * RENDER_SIZE_X) );

			vec2 uv = 2.0f * ( ( pixel_filter( vec2(pixel_coord) ) - ( 0.5f * vec2(resolution) ) ) / glm::max(resolution.x, resolution.y) );

			vec3 ro = vec3(0.0f, 0.0f, 4.0f);
			vec3 rd = normalize( vec3(CAMERA_FOV * uv, -1) );

			vec3 c = radiance(ro, rd);

			if(c.r >= 0.0f && c.g >= 0.0f && c.b >= 0.0f)
			{
				color += radiance(ro, rd);

				samples++;
			}
		}

		color = samples != 0 ? color / float(samples) : color;

		color = clamp(1.0f - glm::exp(-glm::max(color, 0.0f) * EXPOSURE), 0.0f, 1.0f);

		render_buffer.buffer[pixel_coord.x + ( ( (RENDER_SIZE_Y - 1) - pixel_coord.y ) * RENDER_SIZE_X )] = color;
	}
	}

	std::cout << "Writing Render to Disk..." << std::endl;

	write_frame(render_buffer, 0);

	std::cout << "Cleaning Up..." << std::endl;

	render_buffer.cleanup();

	std::cout << "Done!" << std::endl;

	return EXIT_SUCCESS;
}