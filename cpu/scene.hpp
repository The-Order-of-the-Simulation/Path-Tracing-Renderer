#include "common.hpp"

vec3 skyColor(vec3 rd)
{
	// Light Source
	if(dot3(float3(0.0F, 1.0F, 0.0F), rd) > 0.8F)
	{
		return float3f(10.0F);
	}

	float atmosphere = max(dot3(float3(0.0F, 1.0F, 0.0F), rd), 0.0F)+(max(dot3(float3(0.0F, -1.0F, 0.0F), rd), 0.0F)*0.2F)+0.2F;

	return float3f(0.35F*atmosphere);
}

/*
// Ray-Marching Hit Distance
#define hitDist 0.0001F

float DE(vec3 pos)
{
	float minDist = 1000.0F;

	uint32_t seed = 1U;

	for(int i = 0; i < 10; i++)
	{
		// Calculate Sphere Position
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = multiply_vec3f(subtract_vec3f(spherePosition, 0.5F), 2.0F);
		spherePosition = subtract_vec3(pos, spherePosition);
		minDist = min(minDist, dot3(spherePosition, spherePosition));
	}

	return sqrtf(minDist)-0.5F;
}

// SDF Tetrahedron Numerical Normals
vec3 sampleNormal(vec3 pos)
{
	return normalize3(add_vec3(add_vec3(add_vec3(
	multiply_vec3f(float3(-1.0F, -1.0F, -1.0F), DE(add_vec3(pos, multiply_vec3f(float3(-1.0F, -1.0F, -1.0F), hitDist)))),
	multiply_vec3f(float3(-1.0F,  1.0F,  1.0F), DE(add_vec3(pos, multiply_vec3f(float3(-1.0F,  1.0F,  1.0F), hitDist))))),
	multiply_vec3f(float3( 1.0F, -1.0F,  1.0F), DE(add_vec3(pos, multiply_vec3f(float3( 1.0F, -1.0F,  1.0F), hitDist))))),
	multiply_vec3f(float3( 1.0F,  1.0F, -1.0F), DE(add_vec3(pos, multiply_vec3f(float3( 1.0F,  1.0F, -1.0F), hitDist))))));
}

intersection trace(vec3 ro, vec3 rd)
{
	intersection outInt;
	outInt.tMin = -1.0F;
	outInt.tMax = -1.0F;
	outInt.hit = false;

	float t = 0.0F;

	for(int i = 0; i < 128; i++)
	{
		if(t > 32.0F)
		{
			break;
		}

		float td = DE(add_vec3(ro, multiply_vec3f(rd, t)));

		if(td < hitDist)
		{
			outInt.tMin = t;
			outInt.hit = true;
			outInt.normal = sampleNormal(add_vec3(ro, multiply_vec3f(rd, t)));
			return outInt;
		}

		t += td;
	}

	return outInt;
}
*/

intersection process_hit(intersection t0, intersection t1)
{
	if(t1.hit)
	{
		if(t0.hit)
		{
			intersection t;
			t.tMin = min(t0.tMin, t1.tMin);
			t.tMax = max(t0.tMax, t1.tMax);
			t.hit = true;
			t.normal = t0.tMin < t1.tMin ? t0.normal : t1.normal;

			return t;
		}

		return t1;
	}

	return t0;
}

intersection trace(vec3 ro, vec3 rd)
{
	intersection t;
	t.hit = false;

	uint32_t seed = 1U;

	for(int i = 0; i < 8; i++)
	{
		// Calculate Sphere Position
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = multiply_vec3f(subtract_vec3f(spherePosition, 0.5F), 2.0F);

		intersection t0 = sphere(ro, rd, spherePosition, 0.35F);
		t = process_hit(t, t0);
	}

	return t;
}