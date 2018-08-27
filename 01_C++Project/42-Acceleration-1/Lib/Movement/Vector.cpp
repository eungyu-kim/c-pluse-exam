#include "stdafx.h"
#include "Vector.h"
#include <math.h>

Vector::Vector(float degree, float length)
{
	this->degree = degree;
	this->length = length;
}

void Vector::DeltaXY(float &dx, float &dy)
{	// 벡터를 x축과 y축으로 나누는 함수
	dx = sin(degree * pi / 180) * length;
	dy = -cos(degree * pi / 180) * length;
}

Vector &Vector::operator +=(Vector &vector)
{	// this와 vector를 +연산을 해서, 그 결과를 this에 저장하는 메서드

	float thisDX, thisDY;			// this의 dx와 dy을 저장할 변수
	this->DeltaXY(thisDX, thisDY);	// this를 분리 x, y로 분리

	float vectorDX, vectorDY;
	vector.DeltaXY(vectorDX, vectorDY);	// vector를 x, y로 분리

	float resultDX = thisDX + vectorDX;	// x벡터 덧셈 연산
	float resultDY = thisDY + vectorDY;	// y벡터 덧셈 연산

	degree = atan2(resultDY, resultDX) * 180 / pi + 90;
	length = sqrt(resultDX * resultDX + resultDY * resultDY);

	return *this;
}

