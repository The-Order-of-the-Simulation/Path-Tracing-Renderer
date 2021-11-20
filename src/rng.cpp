#include "common.hpp"

// Random Number Generator Seed
uint32_t ns;

void init_rng(uint32_t seed)
{
	ns = seed;
}

// https://nullprogram.com/blog/2018/07/31/
uint32_t triple32(uint32_t x)
{
	x ^= x >> 17u;
	x *= 0xED5AD4BBu;
	x ^= x >> 11u;
	x *= 0xAC4C1B51u;
	x ^= x >> 15u;
	x *= 0x31848BABu;
	x ^= x >> 14u;
	return x;
}

// Random Value Between 0.0 and 1.0
float random_float()
{
	// Update RNG
	ns = triple32(ns);

	return float(ns)/float(0xFFFFFFFFu);
}

// 2-Component Uniform Random Vector
vec2 rand2()
{
	vec2 vector;
	vector.x = random_float();
	vector.y = random_float();
	return vector;
}

// 3-Component Uniform Random Vector
vec3 rand3()
{
	vec3 vector;
	vector.x = random_float();
	vector.y = random_float();
	vector.z = random_float();
	return vector;
}

// 4-Component Uniform Random Vector
vec4 rand4()
{
	vec4 vector;
	vector.x = random_float();
	vector.y = random_float();
	vector.z = random_float();
	vector.w = random_float();
	return vector;
}

// See michael0884's usage of PCG Random
// https://www.shadertoy.com/view/wltcRS
// https://www.shadertoy.com/view/WttyWX

vec2 nrand2(vec2 mean, float sigma)
{
	vec2 z = rand2();
	return mean + sigma * glm::sqrt( -2.0f * glm::log(z.x) ) * vec2( glm::cos(2.0f * pi * z.y), glm::sin(2.0f * pi * z.y) );
}

vec3 nrand3(vec3 mean, float sigma)
{
	vec4 z = rand4();
	return mean + sigma * glm::sqrt( -2.0f * glm::log( vec3(z.x, z.x, z.y ) ) ) * vec3( glm::cos(2.0f * pi * z.z), glm::sin(2.0f * pi * z.z), glm::cos(2.0f * pi * z.w) );
}

vec4 nrand4(vec4 mean, float sigma)
{
	vec4 z = rand4();
	return mean + sigma * glm::sqrt( -2.0f * glm::log( vec4(z.x, z.x, z.y, z.y) ) ) * vec4( glm::cos(2.0f * pi * z.z), glm::sin(2.0f * pi * z.z), glm::cos(2.0f * pi * z.w), glm::sin(2.0f * pi * z.w) );
}

// Random Uniform Direction
vec2 udir2()
{
	float z = rand();
	float r = 2.0f * pi * z;
	float s = glm::sin(r), c = glm::cos(r);
	return vec2(s, c);
}

// Random Uniform Direction
vec3 udir3()
{
	vec2 z = rand2();
	vec2 r = vec2( 2.0f * pi * z.x, acosf(2.0f * z.y - 1.0f) );
	vec2 s = glm::sin(r), c = glm::cos(r);
	return vec3(s.y * c.x, s.x * s.y, c.y);
}