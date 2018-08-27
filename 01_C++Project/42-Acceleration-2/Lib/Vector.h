#pragma once
#include "Matrix.h"

class Vector
{
private:
	float degree;
	float length;

public:
	Vector(float degree, float length);
	void DeltaXY(float &dx, float &dy);
	float GetDegree()
	{
		return degree;
	}
	Vector &operator +=(Vector &vector);
};