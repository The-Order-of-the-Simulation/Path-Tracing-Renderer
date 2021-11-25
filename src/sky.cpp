#include <common.hpp>

vec3 sky_radiance(vec3 dir)
{
	const vec3 sun_dir = normalize( vec3( 1.0f,  1.0f, -1.0f) );

	float d = dot(dir, sun_dir);

	if(d > 0.8f)
	{
		return vec3(5);
	}

	return vec3(1) * (glm::max( (0.8f * dir.y) + 0.15f, 0.0f ) + 0.05f);
}