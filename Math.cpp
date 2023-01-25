#include "Math.h"

unsigned char Math::mod3(const short& num)
{
	short soln = num;
	while (soln > 2)
		soln -= 3;

	while (soln < 0)
		soln += 3;

	return soln;
}

short Math::sign(float number)
{
	if (number < 0)
		return -1;
	else
		return 1;
}

void Math::rotateX(vec3& vec, const float& theta)
{
	mat4x4 matRotX;
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(theta);
	matRotX.m[1][2] = sinf(theta);
	matRotX.m[2][1] = -sinf(theta);
	matRotX.m[2][2] = cosf(theta);
	matRotX.m[3][3] = 1;

	multiplyMatrixVector(vec, matRotX);
}

void Math::rotateZ(vec3& vec, const float& theta)
{
	mat4x4 matRotZ;
	matRotZ.m[0][0] = cosf(theta);
	matRotZ.m[0][1] = sinf(theta);
	matRotZ.m[1][0] = -sinf(theta);
	matRotZ.m[1][1] = cosf(theta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	multiplyMatrixVector(vec, matRotZ);

}

void Math::multiplyMatrixVector(vec3& i, const mat4x4& m)
{
	i.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	i.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	i.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0)
	{
		i.x /= w;
		i.y /= w;
		i.z /= w;
	}
}