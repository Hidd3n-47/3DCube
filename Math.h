#pragma once
#include "vec.h"

class Math
{
public:
	static unsigned char mod3(const short& num);

	static short sign(float number);

	static void rotateX(vec3& vec, const float& theta);
	static void rotateZ(vec3& vec, const float& theta);

	static void multiplyMatrixVector(vec3& i, const mat4x4& m);
private:

};

