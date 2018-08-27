#pragma once
#include "Matrix.h"

class Vector
{
private:
	float degree;		// 벡터의 방향
	float length;		// 벡터의 스칼라

public:
	Vector(float degree, float length);
	void DeltaXY(float &dx, float &dy);	// 벡터를 x축과 y축으로 나누는 함수
	float GetDegree()
	{
		return degree;
	}
	Vector &operator +=(Vector &vector);
};
