#include <cmath>

// 3-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
} vec3;

vec3 float3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

vec3 float3f(float x)
{
	return float3(x, x, x);
}

vec3 add_vec3(vec3 vector0, vec3 vector1)
{
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	vector0.z += vector1.z;
	return vector0;
}

vec3 add_vec3f(vec3 vector, float x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	return vector;
}

vec3 subtract_vec3(vec3 vector0, vec3 vector1)
{
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	vector0.z -= vector1.z;
	return vector0;
}

vec3 subtract_vec3f(vec3 vector, float x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	return vector;
}

vec3 multiply_vec3(vec3 vector0, vec3 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	return vector0;
}

vec3 multiply_vec3f(vec3 vector, float x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	return vector;
}

vec3 divide_vec3(vec3 vector0, vec3 vector1)
{
	vector0.x /= vector1.x;
	vector0.y /= vector1.y;
	vector0.z /= vector1.z;
	return vector0;
}

vec3 divide_vec3f(vec3 vector, float x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	return vector;
}

vec3 negate3(vec3 vector)
{
	return float3(-vector.x, -vector.y, -vector.z);
}

float dot3(vec3 vector0, vec3 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	return vector0.x+vector0.y+vector0.z;
}

// Cross Product
vec3 cross(vec3 vector0, vec3 vector1)
{
	return float3(
	(vector0.y*vector1.z)-(vector1.y*vector0.z),
	(vector0.z*vector1.x)-(vector1.z*vector0.x),
	(vector0.x*vector1.y)-(vector1.x*vector0.y));
}

float length3(vec3 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	vector.z *= vector.z;
	return sqrtf(vector.x+vector.y+vector.z);
}

vec3 normalize3(vec3 vector)
{
	return divide_vec3f(vector, length3(vector));
}

vec3 sin3(vec3 vector)
{
	vector.x = sinf(vector.x);
	vector.y = sinf(vector.y);
	vector.z = sinf(vector.z);
	return vector;
}

vec3 cos3(vec3 vector)
{
	vector.x = cosf(vector.x);
	vector.y = cosf(vector.y);
	vector.z = cosf(vector.z);
	return vector;
}

vec3 sqrt3(vec3 vector)
{
	vector.x = sqrtf(vector.x);
	vector.y = sqrtf(vector.y);
	vector.z = sqrtf(vector.z);
	return vector;
}

vec3 log3(vec3 vector)
{
	vector.x = logf(vector.x);
	vector.y = logf(vector.y);
	vector.z = logf(vector.z);
	return vector;
}

vec3 exp3(vec3 vector)
{
	vector.x = expf(vector.x);
	vector.y = expf(vector.y);
	vector.z = expf(vector.z);
	return vector;
}

// https://asawicki.info/news_1301_reflect_and_refract_functions.html
vec3 reflect3(vec3 vector, vec3 normal)
{
	return subtract_vec3(vector, multiply_vec3f(normal, 2.0F*dot3(vector, normal)));
}