#include <cmath>

// ##### Constants #####

// http://www.mimirgames.com/articles/programming/digits-of-pi-needed-for-floating-point-numbers/
#define pi 3.1415926535897932384626433832795028841971693993751058209749445923078164F

// ##### Data Types #####

// 2-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
} vec2;

// 3-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
} vec3;

// 4-Component Floating-Point Vector
typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

// Intersection Data Bundle
typedef struct {
	float tMin;
	float tMax;
	bool hit;
	vec3 normal;
} intersection;

// ##### Vector Creation #####

inline vec2 float2(float x, float y)
{
	vec2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

inline vec3 float3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

inline vec2 float2f(float x)
{
	return float2(x, x);
}

inline vec3 float3f(float x)
{
	return float3(x, x, x);
}

// ##### Vector Math #####

inline vec2 add_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x+vector1.x, vector0.y+vector1.y);
}

inline vec2 add_vec2f(vec2 vector, float x)
{
	return float2(vector.x+x, vector.y+x);
}

inline vec3 add_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x+vector1.x, vector0.y+vector1.y, vector0.z+vector1.z);
}

inline vec3 add_vec3f(vec3 vector, float x)
{
	return float3(vector.x+x, vector.y+x, vector.z+x);
}

inline vec2 subtract_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x-vector1.x, vector0.y-vector1.y);
}

inline vec2 subtract_vec2f(vec2 vector, float x)
{
	return float2(vector.x-x, vector.y-x);
}

inline vec3 subtract_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x-vector1.x, vector0.y-vector1.y, vector0.z-vector1.z);
}

inline vec3 subtract_vec3f(vec3 vector, float x)
{
	return float3(vector.x-x, vector.y-x, vector.z-x);
}

inline vec2 multiply_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x*vector1.x, vector0.y*vector1.y);
}

inline vec2 multiply_vec2f(vec2 vector, float x)
{
	return float2(vector.x*x, vector.y*x);
}

inline vec3 multiply_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x*vector1.x, vector0.y*vector1.y, vector0.z*vector1.z);
}

inline vec3 multiply_vec3f(vec3 vector, float x)
{
	return float3(vector.x*x, vector.y*x, vector.z*x);
}

inline vec2 divide_vec2(vec2 vector0, vec2 vector1)
{
	return float2(vector0.x/vector1.x, vector0.y/vector1.y);
}

inline vec2 divide_vec2f(vec2 vector, float x)
{
	return float2(vector.x/x, vector.y/x);
}

inline vec3 divide_vec3(vec3 vector0, vec3 vector1)
{
	return float3(vector0.x/vector1.x, vector0.y/vector1.y, vector0.z/vector1.z);
}

inline vec3 divide_vec3f(vec3 vector, float x)
{
	return float3(vector.x/x, vector.y/x, vector.z/x);
}

inline float dot2(vec2 vector0, vec2 vector1)
{
	return (vector0.x*vector1.x)+(vector0.y*vector1.y);
}

inline float dot3(vec3 vector0, vec3 vector1)
{
	return (vector0.x*vector1.x)+(vector0.y*vector1.y)+(vector0.z*vector1.z);
}

inline float length2(vec2 vector)
{
	return sqrtf(dot2(vector, vector));
}

inline float length3(vec3 vector)
{
	return sqrtf(dot3(vector, vector));
}

inline vec2 normalize2(vec2 vector)
{
	return divide_vec2(vector, float2f(length2(vector)));
}

inline vec3 normalize3(vec3 vector)
{
	return divide_vec3(vector, float3f(length3(vector)));
}

inline vec2 sin2(vec2 vector)
{
	return float2(sinf(vector.x), sinf(vector.y));
}

inline vec3 sin3(vec3 vector)
{
	return float3(sinf(vector.x), sinf(vector.y), sinf(vector.z));
}

inline vec2 cos2(vec2 vector)
{
	return float2(cosf(vector.x), cosf(vector.y));
}

inline vec3 cos3(vec3 vector)
{
	return float3(cosf(vector.x), cosf(vector.y), cosf(vector.z));
}

inline vec2 sqrt2(vec2 vector)
{
	return float2(sqrtf(vector.x), sqrtf(vector.y));
}

inline vec3 sqrt3(vec3 vector)
{
	return float3(sqrtf(vector.x), sqrtf(vector.y), sqrtf(vector.z));
}

inline vec2 log2(vec2 vector)
{
	return float2(logf(vector.x), logf(vector.y));
}

inline vec3 log3(vec3 vector)
{
	return float3(logf(vector.x), logf(vector.y), logf(vector.z));
}

inline vec2 exp2(vec2 vector)
{
	return float2(expf(vector.x), expf(vector.y));
}

inline vec3 exp3(vec3 vector)
{
	return float3(expf(vector.x), expf(vector.y), expf(vector.z));
}

// ##### Intersection Functions #####

// Sphere Intersection Function
intersection sphere(vec3 ro, vec3 rd, vec3 sphPos, float sphRad)
{
	intersection t;

	vec3 oc = subtract_vec3(ro, sphPos);
	float b = dot3(oc, rd);
	float c = dot3(oc, oc)-(sphRad*sphRad);
	float h = b*b-c;

	if(h < 0.0F)
	{
		t.tMin = -1.0F;
		t.tMax = -1.0F;
		t.hit = false;
		return t;
	}

	h = sqrtf(h);

	t.tMin = -b-h;
	t.tMax = -b+h;
	t.hit = true;
	t.normal = normalize3(subtract_vec3(add_vec3(ro, multiply_vec3f(rd, t.tMin)), sphPos));

	return t;
}

// ##### Random Number Generator #####

#include <cstdint>

// Random Number Generator Seed
uint32_t ns;

// Triple32 Hash: https://nullprogram.com/blog/2018/07/31/
inline uint32_t triple32(uint32_t x)
{
	x ^= x >> 17U;
	x *= 0xED5AD4BBU;
	x ^= x >> 11U;
	x *= 0xAC4C1B51U;
	x ^= x >> 15U;
	x *= 0x31848BABU;
	x ^= x >> 14U;
	return x;
}

// Uniform Random Value Between 0.0 and 1.0
inline float randomFloat()
{
	ns = triple32(ns);
	return float(ns)/float(0xFFFFFFFFU);
}

// Uniform Random Vectors

inline vec2 rand2()
{
	vec2 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	return vector;
}

inline vec3 rand3()
{
	vec3 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	vector.z = randomFloat();
	return vector;
}

inline vec4 rand4()
{
	vec4 vector;
	vector.x = randomFloat();
	vector.y = randomFloat();
	vector.z = randomFloat();
	vector.w = randomFloat();
	return vector;
}

// Random Uniform Direction
inline vec2 udir2()
{
	float z = randomFloat();
	float r = 2.0F*pi*z;
	float s = sinf(r), c = cosf(r);
	return float2(s, c);
}

inline vec3 udir3()
{
	vec2 z = rand2();
	vec2 r = float2(2.0F*pi*z.x, acosf(2.0F*z.y-1.0F));
	vec2 s = sin2(r), c = cos2(r);
	return float3(c.x*s.y, s.x*s.y, c.y);
}

// See michael0884's usage of PCG Random
// https://www.shadertoy.com/view/wltcRS
// https://www.shadertoy.com/view/WttyWX

// Normalized Random Vectors (Gaussian Distribution)
vec3 nrand3(float sigma, vec3 mean)
{
	vec4 z = rand4();
	return add_vec3(multiply_vec3f(multiply_vec3(sqrt3(multiply_vec3f(log3(float3(z.x, z.x, z.y)), -2.0F)), float3(cosf(2.0F*pi*z.z), sinf(2.0F*pi*z.z), cosf(2.0F*pi*z.w))), sigma), mean);
}

/*


// Normalized Random Vectors (Gaussian Distribution)
vec2 nrand2(float sigma, vec2 mean)
{
	vec2 z = rand2();
	return mean+sigma*sqrt(-2.0*log(z.x   ))*vec2(cos(2.0*pi*z.y), sin(2.0*pi*z.y));
}

vec4 nrand4(float sigma, vec4 mean)
{
	vec4 z = rand4();
	return mean+sigma*sqrt(-2.0*log(z.xxyy))*vec4(cos(2.0*pi*z.z), sin(2.0*pi*z.z), cos(2.0*pi*z.w), sin(2.0*pi*z.w));
}
*/

// ##### Other Functions #####

// HDR Exposure Tonemap
vec3 tonemap(vec3 color, float exposure)
{
	color = multiply_vec3f(color, exposure);

	// Tonemap and Output Color
	return subtract_vec3(float3f(1.0F), exp3(float3(-color.x, -color.y, -color.z)));
}

// Blackman-Harris Pixel Filter
vec2 pixelFilter(vec2 pixelCoord)
{
	// https://en.wikipedia.org/wiki/Window_function#Blackman–Harris_window
	// w[n] = a0-a1*cos(2*pi*n/N)+a2*cos(4*pi*n/N)-a3*cos(6*pi*n/N)
	// a0 = 0.35875; a1 = 0.48829; a2 = 0.14128; a3 = 0.01168
	float n = 0.5F*randomFloat()+0.5F;
	float w = 0.35875F-0.48829F*cos(2.0F*pi*n)+0.14128F*cos(4.0F*pi*n)-0.01168F*cos(6.0F*pi*n);
	return add_vec2(pixelCoord, multiply_vec2f(udir2(), 2.0F*w));
}