#include "common.hpp"


vec3 skyColor(vec3 rd)
{
	// Light Source
	if(dot(vec3(0.0F, 1.0F, 0.0F), rd) > 0.8F)
	{
		return vec3(10.0F);
	}
	vec3 unit_y = vec3(0.0F, 1.0F, 0.0F);
	float atmosphere = max(dot(unit_y, rd), 0.0F)+(max(dot(unit_y * -1.0, rd), 0.0F)*0.2F)+0.2F;

	return vec3(0.35F*atmosphere);
}


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
			t.materialProperties = t0.tMin < t1.tMin ? t0.materialProperties : t1.materialProperties;
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

	//uint32_t seed = 1U;
	uint32_t seed = 420691337U;

	for(int i = 0; i < 32; i++)
	{
		// Calculate Sphere Position
		vec3 spherePosition;
		seed = triple32(seed); spherePosition.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); spherePosition.z = float(seed)/float(0xFFFFFFFFU);
		spherePosition = (spherePosition - vec3(0.5F)) * 2.0F;

		seed = triple32(seed);

		intersection t0 = sphere(ro, rd, spherePosition, max(0.25F*(float(seed)/float(0xFFFFFFFFU)), 0.05F));

		seed = triple32(seed); t0.materialProperties.baseColor.x = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); t0.materialProperties.baseColor.y = float(seed)/float(0xFFFFFFFFU);
		seed = triple32(seed); t0.materialProperties.baseColor.z = float(seed)/float(0xFFFFFFFFU);

		t = process_hit(t, t0);
	}

	t.materialProperties.volume = false;
	//t.materialProperties.baseColor = float3(0.600F, 0.700F, 0.800F);
	t.materialProperties.roughness = randomFloat() < 0.8F ? 0.5F : 0.0F;

	return t;
}
