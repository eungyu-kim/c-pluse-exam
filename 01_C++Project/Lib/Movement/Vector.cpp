#include "stdafx.h"
#include "Vector.h"


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

Vector &Vector::operator +=(Vector &vector)
{	// this와 vector를 +연산을 해서, 그 결과를
	// this에 저장하는 메서드
	// 두 벡터의 합은 두 벡터의 x, y 성분을 각각 더한
	// 벡터와 같으므로
	float myDX, myDY;
	this->DeltaXY(myDX, myDY); // this를 분리 x, y로 분리

	float vectorDX, vectorDY;
	vector.DeltaXY(vectorDX, vectorDY);	// vector를 x, y로 분리

	// 결과벡터를 x, y로 나눈 값
	float resultDX = myDX + vectorDX;
	float resultDY = myDY + vectorDY;

	degree = atan2(resultDY, resultDX) * 180 / pi + 90;
	length = sqrt(resultDX * resultDX + resultDY * resultDY);
	// 길이의 대소를 비교하기 위해서는 sqrt를 씌우지 않고
	// 길이의 제공상태에서 비교할 수 있지만,
	// 여기서는 length는 정확하게 길이값을 가지고 있기 때문에
	// sqrt를 씌워 계산해야 한다.
	// 또한 degree와 length는 모두 this의 멤버변이므로
	// +=연사자답게 자신의 값이 갱신되었다.
	// 마지막으로 this 객체를 반환하면 끝
	return *this;
}