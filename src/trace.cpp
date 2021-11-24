#include "common.hpp"

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

bool inside_bounding_box(vec3 p, vec3 minimum, vec3 maximum)
{
	return
	p.x > minimum.x && p.x < maximum.x &&
	p.y > minimum.y && p.y < maximum.y &&
	p.z > minimum.z && p.z < maximum.z;
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

		if(glm::abs(rayPos.x) > 2.3f || glm::abs(rayPos.y) > 2.3f || rayPos.z > 4.01f || rayPos.z < -2.3f)
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