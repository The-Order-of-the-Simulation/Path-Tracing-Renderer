#include <cmath>

class vec2{
public:
	float x, y;	
	vec2() : x(0), y(0) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}
	vec2(float c) : x(c), y(c) {}
	vec2(const vec2& other) {x = other.x; y = other.y;}

	vec2 operator+(const vec2& other) const { return vec2(x + other.x, y + other.y); }
	vec2 operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }
	vec2 operator*(const vec2& other) const { return vec2(x * other.x, y * other.y); }
	vec2 operator/(const vec2& other) const { return vec2(x / other.x, y / other.y); }
	vec2 operator*(float other) const { return vec2(x * other, y * other); }
	vec2 operator/(float other) const { return vec2(x / other, y / other); }

};

float dot(const vec2& a, const vec2& b){ return a.x * b.x + a.y * b.y; }
float length2(const vec2& a){ return dot(a,a);}
float length(const vec2& a){return sqrtf(length2(a));}
vec2 normalize(const vec2& a){return a / length(a);}
vec2 sin(const vec2& a){ return vec2(sin(a.x), sin(a.y)); }
vec2 cos(const vec2& a){ return vec2(cos(a.x), cos(a.y)); }
vec2 sqrt(const vec2& a){ return vec2(sqrtf(a.x), sqrtf(a.y)); }
vec2 log(const vec2& a){ return vec2(logf(a.x), logf(a.y)); }
vec2 exp(const vec2& a){ return vec2(expf(a.x), expf(a.y)); }


class vec3{
public:
	float x, y, z;
	vec3() : x(0), y(0), z(0) {}
	vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	vec3(float c) : x(c), y(c), z(c) {}
	vec3(const vec3& other) {x = other.x; y = other.y; z = other.z;}

	vec3 operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
	vec3 operator-(const vec3& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
	vec3 operator*(const vec3& other) const { return vec3(x * other.x, y * other.y, z * other.z); }
	vec3 operator/(const vec3& other) const { return vec3(x / other.x, y / other.y, z / other.z); }
	vec3 operator*(float other) const { return vec3(x * other, y * other, z * other); }
	vec3 operator/(float other) const { return vec3(x / other, y / other, z / other);}

};

float dot(const vec3& a, const vec3& b){return a.x * b.x + a.y * b.y + a.z * b.z;}
float length2(const vec3& a){ return dot(a,a);}
float length(const vec3& a){return sqrtf(length2(a));}
vec3 normalize(const vec3& a){return vec3(a / length(a));}
vec3 cross(const vec3& vector0, const vec3& vector1){
	return vec3(
	(vector0.y*vector1.z)-(vector1.y*vector0.z),
	(vector0.z*vector1.x)-(vector1.z*vector0.x),
	(vector0.x*vector1.y)-(vector1.x*vector0.y));
}
vec3 sin(const vec3& a){ return vec3(sin(a.x), sin(a.y), sin(a.z)); }
vec3 cos(const vec3& a){ return vec3(cos(a.x), cos(a.y), cos(a.z)); }
vec3 sqrt(const vec3& a){ return vec3(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z)); }
vec3 log(const vec3& a){ return vec3(logf(a.x), logf(a.y), logf(a.z)); }
vec3 exp(const vec3& a){ return vec3(expf(a.x), expf(a.y), expf(a.z)); }
vec3 reflect(const vec3& vector, const vec3& normal) { return vector - normal * 2.0F * dot(vector, normal);}

class vec4{
public:
	float x, y, z, w;
	vec4() : x(0), y(0), z(0), w(0) {}
	vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	vec4(float c) : x(c), y(c), z(c), w(c) {}
	vec4(const vec4& other) {x = other.x; y = other.y; z = other.z; w = other.w;}

	vec4 operator+(const vec4& other) const { return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
	vec4 operator-(const vec4& other) const { return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
	vec4 operator*(const vec4& other) const { return vec4(x * other.x, y * other.y, z * other.z, w * other.w); }
	vec4 operator/(const vec4& other) const { return vec4(x / other.x, y / other.y, z / other.z, w / other.w); }
	vec4 operator*(float other) const { return vec4(x * other, y * other, z * other, w * other); }
	vec4 operator/(float other) const { return vec4(x / other, y / other, z / other, w / other);}

};

float dot(const vec4& a, const vec4& b){return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;}
float length2(const vec4& a){ return dot(a,a);}
float length(const vec4& a){return sqrtf(length2(a));}
vec4 normalize(const vec4& a){return a / length(a);}
vec4 sin(const vec4& a){ return vec4(sin(a.x), sin(a.y), sin(a.z), sin(a.w)); }
vec4 cos(const vec4& a){ return vec4(cos(a.x), cos(a.y), cos(a.z), cos(a.w)); }
vec4 sqrt(const vec4& a){ return vec4(sqrtf(a.x), sqrtf(a.y), sqrtf(a.z), sqrtf(a.w)); }
vec4 log(const vec4& a){ return vec4(logf(a.x), logf(a.y), logf(a.z), logf(a.w)); }
vec4 exp(const vec4& a){ return vec4(expf(a.x), expf(a.y), expf(a.z), expf(a.w)); }