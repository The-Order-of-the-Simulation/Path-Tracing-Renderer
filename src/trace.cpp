#include <common.hpp>

// SDF Tetrahedron Numerical Normals
vec3 calculate_normal(vec3 p)
{
	unsigned int null_id;

	return normalize(
	vec3(-1, -1, -1) * DE(p + vec3(-1, -1, -1) * HIT_DIST, &null_id) +
	vec3(-1,  1,  1) * DE(p + vec3(-1,  1,  1) * HIT_DIST, &null_id) +
	vec3( 1, -1,  1) * DE(p + vec3( 1, -1,  1) * HIT_DIST, &null_id) +
	vec3( 1,  1, -1) * DE(p + vec3( 1,  1, -1) * HIT_DIST, &null_id)
	);
}

bool inside_bounding_box(vec3 p, vec3 minimum, vec3 maximum)
{
	return
	p.x > minimum.x && p.x < maximum.x &&
	p.y > minimum.y && p.y < maximum.y &&
	p.z > minimum.z && p.z < maximum.z;
}

/*
// Axis-Aligned Bounding Box Intersection
bool intersect_aabb(vec3 minimum, vec3 maximum, vec3 origin, vec3 direction, float *tmin, float *tmax)
{
	vec3 inv_direction = 1.0f / direction;
	vec3 tmin_vec = (minimum - origin) * inv_direction;
	vec3 tmax_vec = (maximum - origin) * inv_direction;

	*tmin = max(max(tmin_vec.x, tmin_vec.y), tmin_vec.z);
	*tmax = min(min(tmax_vec.x, tmax_vec.y), tmax_vec.z);

	return *tmin <= *tmax;
}
*/

raycast process_hit(raycast raycast_data, raycast raycast_data_)
{
	if(raycast_data_.hit)
	{
		if(raycast_data.hit)
		{
			raycast output_data;

			output_data.expire = false;
			output_data.hit = true;

			if(raycast_data.tMin < raycast_data_.tMin)
			{
				output_data.tMin          = raycast_data.tMin;
				output_data.normal        = raycast_data.normal;
				output_data.material_data = raycast_data.material_data;
			}
			else
			{
				output_data.tMin          = raycast_data_.tMin;
				output_data.normal        = raycast_data_.normal;
				output_data.material_data = raycast_data_.material_data;
			}

			if(raycast_data.tMax > raycast_data_.tMax)
			{
				output_data.tMax = raycast_data.tMax;
			}
			else
			{
				output_data.tMax = raycast_data_.tMax;
			}

			return output_data;
		}

		return raycast_data_;
	}

	return raycast_data;
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
	unsigned int id = 0;

	for(unsigned int i = 0; i < MAX_STEPS; i++)
	{
		vec3 rayPos = ro + rd * t;

		//if(glm::abs(rayPos.x) > 2.3f || glm::abs(rayPos.y) > 2.3f || rayPos.z > 4.01f || rayPos.z < -2.3f)
		if(glm::abs(rayPos.x) > 8.0f || glm::abs(rayPos.y) > 8.0f || glm::abs(rayPos.z) > 8.0f)
		{
			raycast_data.expire = false;

			break;
		}

		float td = DE(rayPos, &id);

		if(td < HIT_DIST)
		{
			raycast_data.expire = false;
			raycast_data.hit    = true ;
			raycast_data.tMin   = td   ;
			raycast_data.normal = calculate_normal(rayPos);
			raycast_data.material_data.material_id = id;

			break;
		}

		t += td;
	}

	return raycast_data;
}