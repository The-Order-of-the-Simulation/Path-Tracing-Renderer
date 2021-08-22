#include <cmath>

// 4-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

vec4 float4(float x, float y, float z, float w)
{
	vec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

vec4 float4f(float x)
{
	return float4(x, x, x, x);
}

vec4 add_vec4(vec4 vector0, vec4 vector1)
{
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	vector0.z += vector1.z;
	vector0.w += vector1.w;
	return vector0;
}

vec4 add_vec4f(vec4 vector, float x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	vector.w += x;
	return vector;
}

vec4 subtract_vec4(vec4 vector0, vec4 vector1)
{
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	vector0.z -= vector1.z;
	vector0.w -= vector1.w;
	return vector0;
}

vec4 subtract_vec4f(vec4 vector, float x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	vector.w -= x;
	return vector;
}

vec4 multiply_vec4(vec4 vector0, vec4 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	vector0.w *= vector1.w;
	return vector0;
}

vec4 multiply_vec4f(vec4 vector, float x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	vector.w *= x;
	return vector;
}

vec4 divide_vec4(vec4 vector0, vec4 vector1)
{
	vector0.x /= vector1.x;
	vector0.y /= vector1.y;
	vector0.z /= vector1.z;
	vector0.w /= vector1.w;
	return vector0;
}

vec4 divide_vec4f(vec4 vector, float x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	vector.w /= x;
	return vector;
}

vec4 negate4(vec4 vector)
{
	return float4(-vector.x, -vector.y, -vector.z, -vector.w);
}

float dot4(vec4 vector0, vec4 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	vector0.w *= vector1.w;
	return vector0.x+vector0.y+vector0.z+vector0.w;
}

float length4(vec4 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	vector.z *= vector.z;
	vector.w *= vector.w;
	return sqrtf(vector.x+vector.y+vector.z+vector.w);
}

vec4 normalize4(vec4 vector)
{
	return divide_vec4f(vector, length4(vector));
}

vec4 sin4(vec4 vector)
{
	vector.x = sinf(vector.x);
	vector.y = sinf(vector.y);
	vector.z = sinf(vector.z);
	vector.w = sinf(vector.w);
	return vector;
}

vec4 cos4(vec4 vector)
{
	vector.x = cosf(vector.x);
	vector.y = cosf(vector.y);
	vector.z = cosf(vector.z);
	vector.w = cosf(vector.w);
	return vector;
}

vec4 sqrt4(vec4 vector)
{
	vector.x = sqrtf(vector.x);
	vector.y = sqrtf(vector.y);
	vector.z = sqrtf(vector.z);
	vector.w = sqrtf(vector.w);
	return vector;
}

vec4 log4(vec4 vector)
{
	vector.x = logf(vector.x);
	vector.y = logf(vector.y);
	vector.z = logf(vector.z);
	vector.w = logf(vector.w);
	return vector;
}

vec4 exp4(vec4 vector)
{
	vector.x = expf(vector.x);
	vector.y = expf(vector.y);
	vector.z = expf(vector.z);
	vector.w = expf(vector.w);
	return vector;
}