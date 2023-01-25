#pragma once
#include <cmath>

struct vec2
{
	vec2() { x = 0; y = 0; }
	vec2(const float& x, const float& y) { this->x = x; this->y = y; }

	float x, y;

	friend vec2 operator- (const vec2& v1, const vec2& v2) { return vec2(v1.x - v2.x, v1.y - v2.y); }
};

struct vec3
{
	vec3() { x = 0; y = 0; z = 0; }
	vec3(const float& x, const float& y, const float& z) { this->x = x; this->y = y; this->z = z; }

	float x, y, z;

	float magnitude() { return sqrt(x * x + y * y + z * z); }

	friend void operator+= (vec3& v1, const vec3& v2) { v1.x += v2.x; v1.y += v2.y; v1.z += v2.z; }
	friend void operator-= (vec3& v1, const vec3& v2) { v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z; }
	friend void operator/= (vec3& v1, const float& f) { v1.x /= f; v1.y /= f; v1.z /= f; }
	friend vec3 operator- (const vec3& v1, const vec3& v2) { return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
	friend float operator* (const vec3& v1, const vec3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	friend float operator< (const vec3& v1, const vec3& v2) 
	{
		float lhs = v1 * v2;
		lhs /= (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z) * sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z));
		return acos(lhs) / 3.1415926f * 180;
	}
};

struct mat4x4
{
	float m[4][4] = { 0 };
};