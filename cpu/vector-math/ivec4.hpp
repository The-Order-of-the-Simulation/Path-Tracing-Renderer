#include <cmath>

// 4-Component Integer Vector
typedef struct {
	int x;
	int y;
	int z;
	int w;
} ivec4;

ivec4 int4(int x, int y, int z, int w)
{
	ivec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

ivec4 int4f(int x)
{
	return int4(x, x, x, x);
}

ivec4 add_ivec4(ivec4 vector0, ivec4 vector1)
{
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	vector0.z += vector1.z;
	vector0.w += vector1.w;
	return vector0;
}

ivec4 add_ivec4f(ivec4 vector, int x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	vector.w += x;
	return vector;
}

ivec4 subtract_ivec4(ivec4 vector0, ivec4 vector1)
{
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	vector0.z -= vector1.z;
	vector0.w -= vector1.w;
	return vector0;
}

ivec4 subtract_ivec4f(ivec4 vector, int x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	vector.w -= x;
	return vector;
}

ivec4 multiply_ivec4(ivec4 vector0, ivec4 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	vector0.w *= vector1.w;
	return vector0;
}

ivec4 multiply_ivec4f(ivec4 vector, int x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	vector.w *= x;
	return vector;
}

ivec4 divide_ivec4(ivec4 vector0, ivec4 vector1)
{
	vector0.x /= vector1.x;
	vector0.y /= vector1.y;
	vector0.z /= vector1.z;
	vector0.w /= vector1.w;
	return vector0;
}

ivec4 divide_ivec4f(ivec4 vector, int x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	vector.w /= x;
	return vector;
}

ivec4 inegate4(ivec4 vector)
{
	return int4(-vector.x, -vector.y, -vector.z, -vector.w);
}