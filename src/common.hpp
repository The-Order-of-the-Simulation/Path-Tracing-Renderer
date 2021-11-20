#pragma once

// OpenGL Mathematics
#include <glm/glm.hpp>
using namespace glm;

// ##### Constants #####

// http://www.mimirgames.com/articles/programming/digits-of-pi-needed-for-floating-point-numbers/
const float pi         = 3.141592653589793f;
const float inverse_pi = 0.318309886183790f;

// ##### Classes/Types #####

class material_properties
{
	public:
		unsigned int material_id;
		vec3         base_color ;
		float        roughness  ;
};

class raycast
{
	public:
		bool  expire;
		bool  hit   ;
		float tMin  ;
		float tMax  ;
		vec3  normal;
		material_properties material_data;
};

class image_buffer
{
	public:
		unsigned int buffer_size_x;
		unsigned int buffer_size_y;
		unsigned int buffer_size;
		vec3 *buffer;
	public:
		void allocate(unsigned int size_x, unsigned int size_y)
		{
			buffer_size_x = size_x;
			buffer_size_y = size_y;
			buffer_size = size_x * size_y;
			buffer = (vec3*)malloc(sizeof(vec3) * buffer_size);
		}

		void cleanup()
		{
			free(buffer);
		}
};

// ##### Image Read/Write #####

void write_frame(image_buffer render_buffer, unsigned int frame_number);

// ##### Random Number Generator #####

// https://nullprogram.com/blog/2018/07/31/
uint32_t triple32(uint32_t x);

void init_rng(uint32_t seed);

// Random Value Between 0.0 and 1.0
float random_float();

// 2-Component Uniform Random Vector
vec2 rand2();

// 3-Component Uniform Random Vector
vec3 rand3();

// 4-Component Uniform Random Vector
vec4 rand4();

// See michael0884's usage of PCG Random
// https://www.shadertoy.com/view/wltcRS
// https://www.shadertoy.com/view/WttyWX

vec2 nrand2(vec2 mean, float sigma);

vec3 nrand3(vec3 mean, float sigma);

vec4 nrand4(vec4 mean, float sigma);

// Random Uniform Direction
vec2 udir2();

// Random Uniform Direction
vec3 udir3();