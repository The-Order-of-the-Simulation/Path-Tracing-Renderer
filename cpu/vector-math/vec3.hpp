#include <cmath>

// 3-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
} vec3;

inline vec3 float3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

inline vec3 float3f(float x)
{
	return float3(x, x, x);
}

inline vec3 add_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x+vector1.x, vector0.y+vector1.y, vector0.z+vector1.z);
}

inline vec3 add_vec3f(vec3 vector, float x)
{
	return float3(vector.x+x, vector.y+x, vector.z+x);
}

inline vec3 subtract_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x-vector1.x, vector0.y-vector1.y, vector0.z-vector1.z);
}

inline vec3 subtract_vec3f(vec3 vector, float x)
{
	return float3(vector.x-x, vector.y-x, vector.z-x);
}

inline vec3 multiply_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x*vector1.x, vector0.y*vector1.y, vector0.z*vector1.z);
}

inline vec3 multiply_vec3f(vec3 vector, float x)
{
	return float3(vector.x*x, vector.y*x, vector.z*x);
}

inline vec3 divide_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x/vector1.x, vector0.y/vector1.y, vector0.z/vector1.z);
}

inline vec3 divide_vec3f(vec3 vector, float x)
{
	return float3(vector.x/x, vector.y/x, vector.z/x);
}

inline vec3 negate3(vec3 vector)
{
	return float3(-vector.x, -vector.y, -vector.z);
}

inline float dot3(vec3 vector0, vec3 vector1)
{
	return (vector0.x*vector1.x)+(vector0.y*vector1.y)+(vector0.z*vector1.z);
}

// Cross Product
vec3 cross(vec3 vector0, vec3 vector1)
{
	return float3(
	(vector0.y*vector1.z)-(vector1.y*vector0.z),
	(vector0.z*vector1.x)-(vector1.z*vector0.x),
	(vector0.x*vector1.y)-(vector1.x*vector0.y));
}

inline float length3(vec3 vector)
{
	return sqrtf(dot3(vector, vector));
}

inline vec3 normalize3(vec3 vector)
{
	return divide_vec3(vector, float3f(length3(vector)));
}

inline vec3 sin3(vec3 vector)
{
	return float3(sinf(vector.x), sinf(vector.y), sinf(vector.z));
}

inline vec3 cos3(vec3 vector)
{
	return float3(cosf(vector.x), cosf(vector.y), cosf(vector.z));
}

inline vec3 sqrt3(vec3 vector)
{
	return float3(sqrtf(vector.x), sqrtf(vector.y), sqrtf(vector.z));
}

inline vec3 log3(vec3 vector)
{
	return float3(logf(vector.x), logf(vector.y), logf(vector.z));
}

inline vec3 exp3(vec3 vector)
{
	return float3(expf(vector.x), expf(vector.y), expf(vector.z));
}

// https://asawicki.info/news_1301_reflect_and_refract_functions.html
inline vec3 reflect3(vec3 vector, vec3 normal)
{
	return subtract_vec3(vector, multiply_vec3f(normal, 2.0F*dot3(vector, normal)));
}