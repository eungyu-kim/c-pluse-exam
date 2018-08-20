#include "stdafx.h"
#include "Vector.h"
#include <math.h>

Vector::Vector(float degree, float length)
{
	this->degree = degree;
	this->length = length;
}

void Vector::DeltaXY(float &dx, float &dy)
{
	dx = sin(degree * pi / 180) * length;
	dy = -cos(degree * pi / 180) * length;
}