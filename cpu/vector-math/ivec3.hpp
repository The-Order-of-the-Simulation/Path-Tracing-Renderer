#include <cmath>

// 3-Component inting-Point Vector
typedef struct {
	int x;
	int y;
	int z;
} ivec3;

ivec3 int3(int x, int y, int z)
{
	ivec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

ivec3 int3f(int x)
{
	return int3(x, x, x);
}

ivec3 add_ivec3(ivec3 vector0, ivec3 vector1)
{
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	vector0.z += vector1.z;
	return vector0;
}

ivec3 add_ivec3f(ivec3 vector, int x)
{
	vector.x += x;
	vector.y += x;
	vector.z += x;
	return vector;
}

ivec3 subtract_ivec3(ivec3 vector0, ivec3 vector1)
{
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	vector0.z -= vector1.z;
	return vector0;
}

ivec3 subtract_ivec3f(ivec3 vector, int x)
{
	vector.x -= x;
	vector.y -= x;
	vector.z -= x;
	return vector;
}

ivec3 multiply_ivec3(ivec3 vector0, ivec3 vector1)
{
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	return vector0;
}

ivec3 multiply_ivec3f(ivec3 vector, int x)
{
	vector.x *= x;
	vector.y *= x;
	vector.z *= x;
	return vector;
}

ivec3 divide_ivec3(ivec3 vector0, ivec3 vector1)
{
	vector0.x /= vector1.x;
	vector0.y /= vector1.y;
	vector0.z /= vector1.z;
	return vector0;
}

ivec3 divide_ivec3f(ivec3 vector, int x)
{
	vector.x /= x;
	vector.y /= x;
	vector.z /= x;
	return vector;
}

ivec3 inegate3(ivec3 vector)
{
	return int3(-vector.x, -vector.y, -vector.z);
}