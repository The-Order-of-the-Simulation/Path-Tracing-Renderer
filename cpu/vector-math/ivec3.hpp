#include <cmath>

// 3-Component Integer Vector
typedef struct {
	int x;
	int y;
	int z;
} ivec3;

inline ivec3 int3(int x, int y, int z)
{
	ivec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

inline ivec3 int3f(int x)
{
	return int3(x, x, x);
}

inline ivec3 add_ivec3(ivec3 vector0, ivec3 vector1)
{
	return int3(vector0.x+vector1.x, vector0.y+vector1.y, vector0.z+vector1.z);
}

inline ivec3 add_ivec3f(ivec3 vector, int x)
{
	return int3(vector.x+x, vector.y+x, vector.z+x);
}

inline ivec3 subtract_ivec3(ivec3 vector0, ivec3 vector1)
{
	return int3(vector0.x-vector1.x, vector0.y-vector1.y, vector0.z-vector1.z);
}

inline ivec3 subtract_ivec3f(ivec3 vector, int x)
{
	return int3(vector.x-x, vector.y-x, vector.z-x);
}

inline ivec3 multiply_ivec3(ivec3 vector0, ivec3 vector1)
{
	return int3(vector0.x*vector1.x, vector0.y*vector1.y, vector0.z*vector1.z);
}

inline ivec3 multiply_ivec3f(ivec3 vector, int x)
{
	return int3(vector.x*x, vector.y*x, vector.z*x);
}

inline ivec3 divide_ivec3(ivec3 vector0, ivec3 vector1)
{
	return int3(vector0.x/vector1.x, vector0.y/vector1.y, vector0.z/vector1.z);
}

inline ivec3 divide_ivec3f(ivec3 vector, int x)
{
	return int3(vector.x/x, vector.y/x, vector.z/x);
}

inline ivec3 inegate3(ivec3 vector)
{
	return int3(-vector.x, -vector.y, -vector.z);
}