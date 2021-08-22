#include <cmath>

// 2-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
} vec2;

vec2 float2(float x, float y)
{
	vec2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

vec2 float2f(float x)
{
	return float2(x, x);
}

vec2 add_vec2(vec2 vector0, vec2 vector1)
{
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	return vector0;
}

vec2 add_vec2f(vec2 vector, float x)
{
	vector.x += x;
	vector.y += x;
	return vector;
}

vec2 subtract_vec2(vec2 vector0, vec2 vector1)
{
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	return vector0;
}

vec2 subtract_vec2f(vec2 vector, float x)
{
	vector.x -= x;
	vector.y -= x;
	return vector;
}

vec2 multiply_vec2(vec2 vector0, vec2 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	return vector0;
}

vec2 multiply_vec2f(vec2 vector, float x)
{
	vector.x *= x;
	vector.y *= x;
	return vector;
}

vec2 divide_vec2(vec2 vector0, vec2 vector1)
{
	vector0.x /= vector1.x;
	vector0.y /= vector1.y;
	return vector0;
}

vec2 divide_vec2f(vec2 vector, float x)
{
	vector.x /= x;
	vector.y /= x;
	return vector;
}

vec2 negate2(vec2 vector)
{
	return float2(-vector.x, -vector.y);
}

float dot2(vec2 vector0, vec2 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	return vector0.x+vector0.y;
}

float length2(vec2 vector)
{
	vector.x *= vector.x;
	vector.y *= vector.y;
	return sqrtf(vector.x+vector.y);
}

vec2 normalize2(vec2 vector)
{
	return divide_vec2f(vector, length2(vector));
}

vec2 sin2(vec2 vector)
{
	vector.x = sinf(vector.x);
	vector.y = sinf(vector.y);
	return vector;
}

vec2 cos2(vec2 vector)
{
	vector.x = cosf(vector.x);
	vector.y = cosf(vector.y);
	return vector;
}

vec2 sqrt2(vec2 vector)
{
	vector.x = sqrtf(vector.x);
	vector.y = sqrtf(vector.y);
	return vector;
}

vec2 log2(vec2 vector)
{
	vector.x = logf(vector.x);
	vector.y = logf(vector.y);
	return vector;
}

vec2 exp2(vec2 vector)
{
	vector.x = expf(vector.x);
	vector.y = expf(vector.y);
	return vector;
}