#include <cmath>

// 2-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
} vec2;

inline vec2 float2(float x, float y)
{
	vec2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

inline vec2 float2f(float x)
{
	return float2(x, x);
}

inline vec2 add_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x+vector1.x, vector0.y+vector1.y);
}

inline vec2 add_vec2f(vec2 vector, float x)
{
	return float2(vector.x+x, vector.y+x);
}

inline vec2 subtract_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x-vector1.x, vector0.y-vector1.y);
}

inline vec2 subtract_vec2f(vec2 vector, float x)
{
	return float2(vector.x-x, vector.y-x);
}

inline vec2 multiply_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x*vector1.x, vector0.y*vector1.y);
}

inline vec2 multiply_vec2f(vec2 vector, float x)
{
	return float2(vector.x*x, vector.y*x);
}

inline vec2 divide_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x/vector1.x, vector0.y/vector1.y);
}

inline vec2 divide_vec2f(vec2 vector, float x)
{
	return float2(vector.x/x, vector.y/x);
}

inline vec2 negate2(vec2 vector)
{
	return float2(-vector.x, -vector.y);
}

inline float dot2(vec2 vector0, vec2 vector1)
{
	return (vector0.x*vector1.x)+(vector0.y*vector1.y);
}

inline float length2(vec2 vector)
{
	return sqrtf(dot2(vector, vector));
}

inline vec2 normalize2(vec2 vector)
{
	return divide_vec2(vector, float2f(length2(vector)));
}

inline vec2 sin2(vec2 vector)
{
	return float2(sinf(vector.x), sinf(vector.y));
}

inline vec2 cos2(vec2 vector)
{
	return float2(cosf(vector.x), cosf(vector.y));
}

inline vec2 sqrt2(vec2 vector)
{
	return float2(sqrtf(vector.x), sqrtf(vector.y));
}

inline vec2 log2(vec2 vector)
{
	return float2(logf(vector.x), logf(vector.y));
}

inline vec2 exp2(vec2 vector)
{
	return float2(expf(vector.x), expf(vector.y));
}