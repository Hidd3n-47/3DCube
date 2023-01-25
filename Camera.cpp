#include "Camera.h"

Camera::Camera(const int& width, const int& height) :
	m_width(width),
	m_height(height)
{
	// Empty.
}

void Camera::changePosition(vec3 dir)
{
	m_position -= dir;
}