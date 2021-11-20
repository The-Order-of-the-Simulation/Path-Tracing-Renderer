#include <cmath>

class vec2{
public:
	float x, y;	
	vec2() : x(0), y(0) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}
	vec2(float c) : x(c), y(c) {}

	vec2 operator+(const vec2 other){ return vec2(x + other.x, y + other.y); }
	vec2 operator-(const vec2 other){ return vec2(x - other.x, y - other.y); }
	vec2 operator*(const vec2 other){ return vec2(x * other.x, y * other.y); }
	vec2 operator/(const vec2 other){ return vec2(x / other.x, y / other.y); }
	vec2 operator*(float other) { return vec2(x * other, y * other); }
	vec2 operator/(float other) { return vec2(x / other, y / other); }

};

float dot(vec2 a, vec2 b){ return a.x * b.x + a.y * b.y; }
float length2(vec2 a){ return dot(a,a);}
float length(vec2 a){return sqrtf(length2(a));}
vec2 normalize(vec2 a){return a / length(a);}
vec2 sin(vec2 a){ return vec2(sin(a.x), sin(a.y)); }
vec2 cos(vec2 a){ return vec2(cos(a.x), cos(a.y)); }
vec2 sqrt(vec2 a){ return vec2(sqrtf(a.x), sqrtf(a.y)); }
vec2 log(vec2 a){ return vec2(logf(a.x), logf(a.y)); }
vec2 exp(vec2 a){ return vec2(expf(a.x), expf(a.y)); }


class vec3{
public:
	float x, y, z;
	vec3() : x(0), y(0), z(0) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	vec3(float c) : x(c), y(c), z(c) {}

	vec3 operator+(const vec3 other){ return vec3(x + other.x, y + other.y, z + other.z); }
	vec3 operator-(const vec3 other){ return vec3(x - other.x, y - other.y, z - other.z); }
	vec3 operator*(const vec3 other){ return vec3(x * other.x, y * other.y, z * other.z); }
	vec3 operator/(const vec3 other){ return vec3(x / other.x, y / other.y, z / other.z); }
	vec3 operator*(float other){ return vec3(x * other, y * other, z * other); }
	vec3 operator/(float other){ return vec3(x / other, y / other, z / other);}

};

float dot(vec3 a, vec3 b){return a.x * b.x + a.y * b.y + a.z * b.z;}
float length2(vec3 a){ return dot(a,a);}
float length(vec3 a){return sqrtf(length2(a));}
vec3 normalize(vec3 a){return a / length(a);}
vec3 cross(vec3 vector0, vec3 vector1){
	return vec3(
	(vector0.y*vector1.z)-(vector1.y*vector0.z),
	(vector0.z*vector1.x)-(vector1.z*vector0.x),
	(vector0.x*vector1.y)-(vector1.x*vector0.y));
}
vec3 sin(vec3 a){ return vec3(sin(a.x), sin(a.y), sin(a.z)); }
vec3 cos(vec3 a){ return vec3(cos(a.x), cos(a.y), cos(a.z)); }
vec3 sqrt(vec3 a){ return vec3(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z)); }
vec3 log(vec3 a){ return vec3(logf(a.x), logf(a.y), logf(a.z)); }
vec3 exp(vec3 a){ return vec3(expf(a.x), expf(a.y), expf(a.z)); }
vec3 reflect(vec3 vector, vec3 normal) { return vector - normal * 2.0F * dot(vector, normal);}

class vec4{
public:
	float x, y, z, w;
	vec4() : x(0), y(0), z(0), w(0) {}
	vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	vec4(float c) : x(c), y(c), z(c), w(c) {}

	vec4 operator+(const vec4 other){ return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
	vec4 operator-(const vec4 other){ return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
	vec4 operator*(const vec4 other){ return vec4(x * other.x, y * other.y, z * other.z, w * other.w); }
	vec4 operator/(const vec4 other){ return vec4(x / other.x, y / other.y, z / other.z, w / other.w); }
	vec4 operator*(float other){ return vec4(x * other, y * other, z * other, w * other); }
	vec4 operator/(float other){ return vec4(x / other, y / other, z / other, w / other);}

};

float dot(vec4 a, vec4 b){return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;}
float length2(vec4 a){ return dot(a,a);}
float length(vec4 a){return sqrtf(length2(a));}
vec4 normalize(vec4 a){return a / length(a);}
vec4 sin(vec4 a){ return vec4(sin(a.x), sin(a.y), sin(a.z), sin(a.w)); }
vec4 cos(vec4 a){ return vec4(cos(a.x), cos(a.y), cos(a.z), cos(a.w)); }
vec4 sqrt(vec4 a){ return vec4(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z), sqrtf(a.w)); }
vec4 log(vec4 a){ return vec4(logf(a.x), logf(a.y), logf(a.z), logf(a.w)); }
vec4 exp(vec4 a){ return vec4(expf(a.x), expf(a.y), expf(a.z), expf(a.w)); }



