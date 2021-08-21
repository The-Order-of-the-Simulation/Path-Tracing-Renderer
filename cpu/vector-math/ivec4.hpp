#include <cmath>

// 4-Component Integer Vector
typedef struct {
	int x;
	int y;
	int z;
	int w;
} ivec4;

inline ivec4 int4(int x, int y, int z, int w)
{
	ivec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

inline ivec4 int4f(int x)
{
	return int4(x, x, x, x);
}

inline ivec4 add_ivec4(ivec4 vector0, ivec4 vector1)
{
	return int4(vector0.x+vector1.x, vector0.y+vector1.y, vector0.z+vector1.z, vector0.w+vector1.w);
}

inline ivec4 add_ivec4f(ivec4 vector, int x)
{
	return int4(vector.x+x, vector.y+x, vector.z+x, vector.w+x);
}

inline ivec4 subtract_ivec4(ivec4 vector0, ivec4 vector1)
{
	return int4(vector0.x-vector1.x, vector0.y-vector1.y, vector0.z-vector1.z, vector0.w-vector1.w);
}

inline ivec4 subtract_ivec4f(ivec4 vector, int x)
{
	return int4(vector.x-x, vector.y-x, vector.z-x, vector.w-x);
}

inline ivec4 multiply_ivec4(ivec4 vector0, ivec4 vector1)
{
	return int4(vector0.x*vector1.x, vector0.y*vector1.y, vector0.z*vector1.z, vector0.w*vector1.w);
}

inline ivec4 multiply_ivec4f(ivec4 vector, int x)
{
	return int4(vector.x*x, vector.y*x, vector.z*x, vector.w*x);
}

inline ivec4 divide_ivec4(ivec4 vector0, ivec4 vector1)
{
	return int4(vector0.x/vector1.x, vector0.y/vector1.y, vector0.z/vector1.z, vector0.w/vector1.w);
}

inline ivec4 divide_ivec4f(ivec4 vector, int x)
{
	return int4(vector.x/x, vector.y/x, vector.z/x, vector.w/x);
}

inline ivec4 negate4(ivec4 vector)
{
	return int4(-vector.x, -vector.y, -vector.z, -vector.w);
}