#include <common.hpp>

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

float DE(vec3 p, unsigned int *id)
{
	*id = 1;

	float l = length(p);

	if(l > 2.3f)
	{
		return l - 2.2f;
	}

	return mandelbulb(p);
}

/*
float DE(vec3 p, unsigned int *id)
{
	float DE0 = p.y + 1.0f; // Plane
	float DE1 = length(p) - 1.0f; // Sphere

	float minDE = glm::min(DE0, DE1);

	*id = 0; // Null
	*id = (minDE == DE0) ? 1 : *id; // Plane
	*id = (minDE == DE1) ? 2 : *id; // Sphere

	return minDE;
}
*/

void update_material(raycast *raycast_data)
{
	if(raycast_data->material_data.material_id == 1)
	{
		raycast_data->material_data.base_color = vec3(0.8f);
		raycast_data->material_data.roughness  = 0.3f;
	}
	else if(raycast_data->material_data.material_id == 2)
	{
		raycast_data->material_data.base_color = vec3(0.8f);
		raycast_data->material_data.roughness  = 0.3f;
	}
	else
	{
		raycast_data->material_data.base_color = vec3(1.0f, 0.0f, 1.0f);
		raycast_data->material_data.roughness  = 0.3f;
	}
}