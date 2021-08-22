#pragma once

#include <cmath>
using namespace std;

// ##### Constants #####

// http://www.mimirgames.com/articles/programming/digits-of-pi-needed-for-floating-point-numbers/
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923078164F

// ##### Data Types #####

#include "vector-math/vec2.hpp"
#include "vector-math/ivec2.hpp"

#include "vector-math/vec3.hpp"
#include "vector-math/ivec3.hpp"

#include "vector-math/vec4.hpp"
#include "vector-math/ivec4.hpp"

// Material Properties Data
typedef struct {
	// Type of Material
	bool volume;

	// Surface/Volume Color
	vec3 baseColor;

	// Surface Roughness
	float roughness;

	// Volume Anisotropy
	float anisotropy;
} material;

// Intersection Data
typedef struct {
	float tMin;
	float tMax;
	bool hit;
	vec3 normal;
	material materialProperties;
} intersection;

// ##### Intersection Functions #####

// A lot of these came from Inigo Quilez:
// https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

// Sphere Intersection Function
inline intersection sphere(vec3 ro, vec3 rd, vec3 sphPos, float sphRad)
{
	intersection t;

	vec3 oc = subtract_vec3(ro, sphPos);
	float b = dot3(oc, rd);
	float c = dot3(oc, oc)-(sphRad*sphRad);
	float h = b*b-c;

	if(h < 0.0F)
	{
		t.tMin = -1.0F;
		t.tMax = -1.0F;
		t.hit = false;
		return t;
	}

	h = sqrtf(h);

	t.tMin = -b-h;
	t.tMax = -b+h;
	t.hit = true;
	t.normal = normalize3(subtract_vec3(add_vec3(ro, multiply_vec3f(rd, t.tMin)), sphPos));

	return t;
}

// Triangle Intersection Function
vec3 triangleInt(vec3 ro, vec3 rd, vec3 v0, vec3 v1, vec3 v2 )
{
	vec3 v1v0 = subtract_vec3(v1, v0);
	vec3 v2v0 = subtract_vec3(v2, v0);
	vec3 rov0 = subtract_vec3(ro, v0);
	vec3  n = cross(v1v0, v2v0);
	vec3  q = cross(rov0, rd  );
	float d = 1.0F/dot3(rd, n);
	float u = d*dot3(negate3(q), v2v0);
	float v = d*dot3(        q , v1v0);
	float t = d*dot3(negate3(n), rov0);
	if(u < 0.0F || u > 1.0F || v < 0.0F || (u+v) > 1.0F )
	{
		t = -1.0F;
	}
	return float3(t, u, v);
}

// ##### Random Number Generator #####

#include <cstdint>

// Random Number Generator Seed
uint32_t ns;

// Triple32 Hash: https://nullprogram.com/blog/2018/07/31/
inline uint32_t triple32(uint32_t x)
{
	x ^= x >> 17U;
	x *= 0xED5AD4BBU;
	x ^= x >> 11U;
	x *= 0xAC4C1B51U;
	x ^= x >> 15U;
	x *= 0x31848BABU;
	x ^= x >> 14U;
	return x;
}

// Uniform Random Value Between 0.0 and 1.0
inline float randomFloat()
{
	ns = triple32(ns);
	return float(ns)/float(0xFFFFFFFFU);
}

// Uniform Random Vectors

inline vec2 rand2()
{
	vec2 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	return vector;
}

inline vec3 rand3()
{
	vec3 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	vector.z = randomFloat();
	return vector;
}

inline vec4 rand4()
{
	vec4 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	vector.z = randomFloat();
	vector.w = randomFloat();
	return vector;
}

// Random Uniform Direction

inline vec2 udir2()
{
	float z = randomFloat();
	float r = 2.0F*pi*z;
	float s = sinf(r), c = cosf(r);
	return float2(s, c);
}

inline vec3 udir3()
{
	vec2 z = rand2();
	vec2 r = float2(2.0F*pi*z.x, acosf(2.0F*z.y-1.0F));
	vec2 s = sin2(r), c = cos2(r);
	return float3(c.x*s.y, s.x*s.y, c.y);
}

/* [insert udir4() here] */

// See michael0884's usage of PCG Random
// https://www.shadertoy.com/view/wltcRS
// https://www.shadertoy.com/view/WttyWX

// Normalized Random Vectors (Gaussian Distribution)

inline vec2 nrand2(float sigma, vec2 mean)
{
	vec2 z = rand2();
	return add_vec2(multiply_vec2f(float2(cosf(2.0F*pi*z.y), sinf(2.0F*pi*z.y)), sigma*sqrtf(-2.0F*logf(z.x))), mean);
}

inline vec3 nrand3(float sigma, vec3 mean)
{
	vec4 z = rand4();
	return add_vec3(multiply_vec3f(multiply_vec3(sqrt3(multiply_vec3f(log3(float3(z.x, z.x, z.y     )), -2.0F)), float3(cosf(2.0F*pi*z.z), sinf(2.0F*pi*z.z), cosf(2.0F*pi*z.w))), sigma), mean);
}

inline vec4 nrand4(float sigma, vec4 mean)
{
	vec4 z = rand4();
	return add_vec4(multiply_vec4f(multiply_vec4(sqrt4(multiply_vec4f(log4(float4(z.x, z.x, z.y, z.y)), -2.0F)), float4(cosf(2.0F*pi*z.z), sinf(2.0F*pi*z.z), cosf(2.0F*pi*z.w), sinf(2.0F*pi*z.w))), sigma), mean);
}

// ##### Other Functions #####

// HDR Exposure Tonemap
inline vec3 tonemap(vec3 color, float exposure)
{
	color = multiply_vec3f(color, exposure);

	// Tonemap and Output Color
	return subtract_vec3(float3f(1.0F), exp3(negate3(color)));
}

// Blackman-Harris Pixel Filter
inline vec2 pixelFilter(vec2 pixelCoord)
{
	// https://en.wikipedia.org/wiki/Window_function#Blackman–Harris_window
	// w[n] = a0-a1*cos(2*pi*n/N)+a2*cos(4*pi*n/N)-a3*cos(6*pi*n/N)
	// a0 = 0.35875; a1 = 0.48829; a2 = 0.14128; a3 = 0.01168
	float n = 0.5F*randomFloat()+0.5F;
	float w = 0.35875F-0.48829F*cos(2.0F*pi*n)+0.14128F*cos(4.0F*pi*n)-0.01168F*cos(6.0F*pi*n);
	return add_vec2(pixelCoord, multiply_vec2f(udir2(), 2.0F*w));
}