#include <cmath>

// 4-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

inline vec4 float4(float x, float y, float z, float w)
{
	vec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

inline vec4 float4f(float x)
{
	return float4(x, x, x, x);
}

inline vec4 add_vec4(vec4 vector0, vec4 vector1)
{
	return float4(vector0.x+vector1.x, vector0.y+vector1.y, vector0.z+vector1.z, vector0.w+vector1.w);
}

inline vec4 add_vec4f(vec4 vector, float x)
{
	return float4(vector.x+x, vector.y+x, vector.z+x, vector.w+x);
}

inline vec4 subtract_vec4(vec4 vector0, vec4 vector1)
{
	return float4(vector0.x-vector1.x, vector0.y-vector1.y, vector0.z-vector1.z, vector0.w-vector1.w);
}

inline vec4 subtract_vec4f(vec4 vector, float x)
{
	return float4(vector.x-x, vector.y-x, vector.z-x, vector.w-x);
}

inline vec4 multiply_vec4(vec4 vector0, vec4 vector1)
{
	return float4(vector0.x*vector1.x, vector0.y*vector1.y, vector0.z*vector1.z, vector0.w*vector1.w);
}

inline vec4 multiply_vec4f(vec4 vector, float x)
{
	return float4(vector.x*x, vector.y*x, vector.z*x, vector.w*x);
}

inline vec4 divide_vec4(vec4 vector0, vec4 vector1)
{
	return float4(vector0.x/vector1.x, vector0.y/vector1.y, vector0.z/vector1.z, vector0.w/vector1.w);
}

inline vec4 divide_vec4f(vec4 vector, float x)
{
	return float4(vector.x/x, vector.y/x, vector.z/x, vector.w/x);
}

inline vec4 negate4(vec4 vector)
{
	return float4(-vector.x, -vector.y, -vector.z, -vector.w);
}

inline float dot4(vec4 vector0, vec4 vector1)
{
	return (vector0.x*vector1.x)+(vector0.y*vector1.y)+(vector0.z*vector1.z)+(vector0.w*vector1.w);
}

inline float length4(vec4 vector)
{
	return sqrtf(dot4(vector, vector));
}

inline vec4 normalize4(vec4 vector)
{
	return divide_vec4(vector, float4f(length4(vector)));
}

inline vec4 sin4(vec4 vector)
{
	return float4(sinf(vector.x), sinf(vector.y), sinf(vector.z), sinf(vector.w));
}

inline vec4 cos4(vec4 vector)
{
	return float4(cosf(vector.x), cosf(vector.y), cosf(vector.z), cosf(vector.w));
}

inline vec4 sqrt4(vec4 vector)
{
	return float4(sqrtf(vector.x), sqrtf(vector.y), sqrtf(vector.z), sqrtf(vector.w));
}

inline vec4 log4(vec4 vector)
{
	return float4(logf(vector.x), logf(vector.y), logf(vector.z), logf(vector.w));
}

inline vec4 exp4(vec4 vector)
{
	return float4(expf(vector.x), expf(vector.y), expf(vector.z), expf(vector.w));
}