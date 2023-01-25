#pragma once
#include "vec.h"

class Camera
{
public:
	Camera(const int& width, const int& height);

	void changePosition(vec3 dir);

	// Getters.
	vec3 getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
private:
	int m_width;
	int m_height;
	vec3 m_position;
};

