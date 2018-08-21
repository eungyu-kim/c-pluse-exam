#pragma once

const float pi = 3.14159;
class Matrix33;

class Matrix31
{
private:
	float matrix[3];

public:
	Matrix31();
	Matrix31(float x, float y);
	float GetX();
	float GetY();

	friend Matrix33;
};

class Matrix33
{
private:
	float matrix[3][3];

public:
	Matrix33();
	void ParallelMoveMent(float dx, float dy);		// 행렬을 평행이동 행령
	void RotationMovement(float degree);			// 회전용 매트릭스로 만듦(인수는 degree)
	void ParallelMovement(float dx, float dy);

	Matrix31 operator *(Matrix31 &matrix31);
	Matrix33 operator *(Matrix33 &matrix33);
};