#include "common.hpp"

vec3 sky_radiance(vec3 rd)
{
	//float d = dot(vec3(0.0f, 1.0f, 0.0f), rd);
	float d = rd.y;

	if(d > 0.5f)
	{
		return vec3(2);
	}

	return vec3(1) * (glm::max( (0.8f * d) + 0.15f, 0.0f ) + 0.05f);
}

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

float DE(vec3 p)
{
	float l = length(p);

	if(l > 2.3f)
	{
		return l - 2.2f;
	}

	return mandelbulb(p);
}