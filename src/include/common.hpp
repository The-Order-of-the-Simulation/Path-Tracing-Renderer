#pragma once

// OpenGL Mathematics
#include <glm/glm.hpp>
using namespace glm;

// ##### Parameters #####

// Camera Field of View
#define CAMERA_FOV 0.5f

// Tonemap Exposure Parameter (only if HDR is disabled)
#define EXPOSURE 1.0f

// Portable FloatMap
//#define HDR

// Ray-Marching Tolerance
#define HIT_DIST 0.003f

// Maximum Path-Tracing Bounces
#define MAX_BOUNCES 16

// Maximum Samples
#define MAX_SAMPLES 32

// Maximum Ray-Marching Steps
#define MAX_STEPS 512

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
		unsigned int size_x;
		unsigned int size_y;
		unsigned int size;
		vec3 *buffer;
	public:
		void allocate(unsigned int buffer_size_x, unsigned int buffer_size_y)
		{
			size_x = buffer_size_x;
			size_y = buffer_size_y;
			size = buffer_size_x * buffer_size_y;
			buffer = (vec3*)malloc(sizeof(vec3) * size);
		}

		void cleanup()
		{
			free(buffer);
		}
};

// ##### Image Read/Write #####

void write_render(image_buffer render_buffer);

void write_render_HDR(image_buffer render_buffer);

void write_frame(image_buffer render_buffer, unsigned int frame_number);

// ##### Random Number Generator #####

// https://nullprogram.com/blog/2018/07/31/
//uint32_t triple32(uint32_t x);

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

// ##### Scene #####

float DE(vec3 p, unsigned int *id);

void update_material(raycast *raycast_data);

// ##### Ray-Tracing/Ray-Marching #####

raycast process_hit(raycast raycast_data, raycast raycast_data_);

raycast trace(vec3 ro, vec3 rd);

// ##### Rendering #####

vec3 sky_radiance(vec3 rd);

vec3 radiance(vec3 ro, vec3 rd);