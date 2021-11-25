#pragma once

#include <cmath>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

#include "vectormath.hpp"

// ##### Constants #####

// http://www.mimirgames.com/articles/programming/digits-of-pi-needed-for-floating-point-numbers/
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923078164F

// ##### Data Types #####


// Material Properties Data
class material {
public:
	bool volume;
	vec3 baseColor;
	float roughness;
	float anisotropy;
};

// Intersection Data
class intersection {
public:
	float tMin = -1.0;
	float tMax = -1.0;
	bool hit = false;
	vec3 normal;
	material materialProperties;
};

class buffer{
private:
	int size_x, size_y;
	vec3 *image_buffer;
public:
	buffer(int _size_x, int _size_y) : size_x(_size_x), size_y(_size_y) { image_buffer = new vec3 [size_x * size_y]; }

	void set_pixel(int x, int y, const vec3& color){ image_buffer[x + (y * size_x)] = color; }	
	void write_buffer(const char* filename){
		std::ofstream imageFile;
		imageFile.open(filename);

		imageFile << "P3" << std::endl << size_x << " " << size_y << std::endl << "65535" << std::endl;

		for(int i = 0; i < size_x * size_y; i++)
		{
			// Quantization
			int channel_r = std::min(std::max(int(65535.0F*image_buffer[i].x), 0), 65535);
			int channel_g = std::min(std::max(int(65535.0F*image_buffer[i].y), 0), 65535);
			int channel_b = std::min(std::max(int(65535.0F*image_buffer[i].z), 0), 65535);

			imageFile << channel_r << " " << channel_g << " " << channel_b << " ";
		}

		imageFile << "# Rendered with OpenPT";
		imageFile.close();
	} 
};

// ##### Intersection Functions #####

// A lot of these came from Inigo Quilez:
// https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

// Sphere Intersection Function
intersection sphere(vec3 ro, vec3 rd, vec3 sphPos, float sphRad) {
	intersection t;

	vec3 oc = ro - sphPos;
	float b = dot(oc, rd);
	float c = dot(oc, oc)-(sphRad*sphRad);
	float h = b*b-c;

	if(h < 0.0F) return t;
	
	h = sqrtf(h);
	t.tMin = -b-h;

	if(t.tMin < 0.0F) return t;

	t.tMax = -b+h;
	t.hit = true;
	t.normal = normalize(ro + (rd * t.tMin) - sphPos);

	return t;
}

// Triangle Intersection Function
vec3 triangleInt(vec3 ro, vec3 rd, vec3 v0, vec3 v1, vec3 v2 )
{
	vec3 v1v0 = v1 - v0;
	vec3 v2v0 = v2 - v0;
	vec3 rov0 = ro - v0;
	vec3  n = cross(v1v0, v2v0);
	vec3  q = cross(rov0, rd  );
	float d = 1.0F/dot(rd, n);
	float u = d*dot(q * -1.0, v2v0);
	float v = d*dot(        q , v1v0);
	float t = d*dot(n * -1.0, rov0);
	if(u < 0.0F || u > 1.0F || v < 0.0F || (u+v) > 1.0F )
	{
		t = -1.0F;
	}
	return vec3(t, u, v);
}

// ##### Random Number Generator #####

// Random Number Generator Seed
uint32_t ns;

// Triple32 Hash: https://nullprogram.com/blog/2018/07/31/
uint32_t triple32(uint32_t x){
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
float randomFloat(){
	ns = triple32(ns);
	return float(ns)/float(0xFFFFFFFFU);
}

// Uniform Random Vectors

vec2 rand2(){return vec2(randomFloat(), randomFloat());}
vec3 rand3(){return vec3(randomFloat(), randomFloat(), randomFloat());}
vec4 rand4(){return vec4(randomFloat(), randomFloat(), randomFloat(), randomFloat());}

// Random Uniform Direction

vec2 udir2()
{
	float z = randomFloat();
	float r = 2.0F*pi*z;
	float s = sinf(r), c = cosf(r);
	return vec2(s, c);
}

vec3 udir3()
{
	vec2 z = rand2();
	vec2 r = vec2(2.0F*pi*z.x, acosf(2.0F*z.y-1.0F));
	vec2 s = sin(r), c = cos(r);
	return vec3(c.x*s.y, s.x*s.y, c.y);
}

/* [insert udir4() here] */

// See michael0884's usage of PCG Random
// https://www.shadertoy.com/view/wltcRS
// https://www.shadertoy.com/view/WttyWX

// Normalized Random Vectors (Gaussian Distribution)

vec2 nrand2(float sigma, vec2 mean)
{
	vec2 z = rand2();
	return (vec2(cosf(2.0F*pi*z.y), sinf(2.0F*pi*z.y)) * sigma*sqrtf(-2.0F*logf(z.x))) + mean;
}

vec3 nrand3(float sigma, vec3 mean)
{
	vec4 z = rand4();
	return ((sqrt((log(vec3(z.x, z.x, z.y)) * -2.0F)) * vec3(cosf(2.0F*pi*z.z), sinf(2.0F*pi*z.z), cosf(2.0F*pi*z.w))) * sigma) + mean;
}

vec4 nrand4(float sigma, vec4 mean)
{
	vec4 z = rand4();
	return ((sqrt((log(vec4(z.x, z.x, z.y, z.y)) * -2.0F)) * vec4(cosf(2.0F*pi*z.z), sinf(2.0F*pi*z.z), cosf(2.0F*pi*z.w), sinf(2.0F*pi*z.w))) * sigma) + mean;
}

// ##### Other Functions #####

// HDR Exposure Tonemap
vec3 tonemap(vec3 color, float exposure)
{
	vec3 tonedcolor = color * exposure;
	// Tonemap and Output Color
	return vec3(1.0F) - exp(tonedcolor * -1.0);
}

// Blackman-Harris Pixel Filter
vec2 pixelFilter(vec2 pixelCoord)
{
	// https://en.wikipedia.org/wiki/Window_function#Blackman–Harris_window
	// w[n] = a0-a1*cos(2*pi*n/N)+a2*cos(4*pi*n/N)-a3*cos(6*pi*n/N)
	// a0 = 0.35875; a1 = 0.48829; a2 = 0.14128; a3 = 0.01168

	const float a0 = 0.35875F;
	const float a1 = 0.48829F;
	const float a2 = 0.14128F;
	const float a3 = 0.01168F;

	float n = 0.5F*randomFloat()+0.5F;
	float w = a0-a1*cosf(2.0F*pi*n)+a2*cosf(4.0*pi*n)-a3*cosf(6.0F*pi*n);

	return pixelCoord + (udir2() * 2.0F * w);
}