#include <iostream>

#include "common.hpp"

// ##### #####

#define CAMERA_FOV 1.0f

#define EXPOSURE 1.0f

#define HIT_DIST 0.003f

#define MAX_BOUNCES 5

#define MAX_SAMPLES 32

#define MAX_STEPS 512

/*
// http://blog.hvidtfeldts.net/index.php/2011/09/distance-estimated-3d-fractals-v-the-mandelbulb-different-de-approximations/
float mandelbulb(vec3 p)
{
	const float power = 8;

	p = vec3(p.x, p.z, p.y);

	vec3 z = p;
	float dr = 1;
	float r  = 0;

	for(unsigned int i = 0; i < 128; i++)
	{
		r = length(z);

		if(r > 4.0f)
		{
			break;
		}

		// Convert to Polar Coordinates
		float theta = glm::acos(z.z/r   );
		float phi   = glm::atan(z.y, z.x);
		dr = glm::pow(r, power - 1.0f) * power * dr + 1.0;

		// Scale and Rotate the Point
		float zr = glm::pow(r, power);
		theta = theta * power;
		phi   = phi   * power;

		float sin_theta = glm::sin(theta);
		float cos_theta = glm::cos(theta);
		float sin_phi = glm::sin(phi);
		float cos_phi = glm::cos(phi);

		// Convert back to Cartesian Coordinates
		z = zr * vec3(sin_theta * cos_phi, sin_theta * sin_phi, cos_theta);

		z += p;
	}

	return 0.5f * glm::log(r) * r / dr;
}
*/

float DE(vec3 p)
{
	float DE0 = length(p) - 1.0f;

	float minDE = DE0;

	return minDE;
}

// SDF Tetrahedron Numerical Normals
vec3 calculate_normal(vec3 p)
{
	return normalize(
	vec3(-1, -1, -1) * DE(p + vec3(-1, -1, -1) * HIT_DIST) +
	vec3(-1,  1,  1) * DE(p + vec3(-1,  1,  1) * HIT_DIST) +
	vec3( 1, -1,  1) * DE(p + vec3( 1, -1,  1) * HIT_DIST) +
	vec3( 1,  1, -1) * DE(p + vec3( 1,  1, -1) * HIT_DIST)
	);
}

raycast trace(vec3 ro, vec3 rd)
{
	raycast raycast_data;

	raycast_data.expire = true   ;
	raycast_data.hit    = false  ;
	raycast_data.tMin   = -1.0f  ;
	raycast_data.tMax   = -1.0f  ;
	raycast_data.normal = vec3(0);
	raycast_data.material_data.material_id = 0;

	float t = 0;

	for(unsigned int i = 0; i < MAX_STEPS; i++)
	{
		vec3 rayPos = ro + rd * t;

		if(glm::abs(rayPos.x) > 2.0f || glm::abs(rayPos.y) > 2.0f || glm::abs(rayPos.z) > 2.1f)
		{
			raycast_data.expire = false;

			break;
		}

		float td = DE(rayPos);

		if(td < HIT_DIST)
		{
			raycast_data.expire = false;
			raycast_data.hit    = true ;
			raycast_data.tMin   = td   ;
			raycast_data.normal = calculate_normal(rayPos);

			break;
		}

		t += td;
	}

	return raycast_data;
}

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

vec3 sky_radiance(vec3 rd)
{
	float d = dot(vec3(0.0f, 1.0f, 0.0f), rd);

	if(d > 0.8f)
	{
		return vec3(5.0f);
	}

	return vec3(0.2f);
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

int main()
{
	const unsigned int RENDER_SIZE_X = 640;
	const unsigned int RENDER_SIZE_Y = 360;
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

			vec2 uv = 2.0f * ( ( vec2(pixel_coord) - ( 0.5f * vec2(resolution) ) ) / glm::max(resolution.x, resolution.y) );

			vec3 ro = vec3(0.0f, 0.0f, 2.0f);
			vec3 rd = normalize( vec3(CAMERA_FOV * uv, -1) );

			color += radiance(ro, rd);

			samples++;
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