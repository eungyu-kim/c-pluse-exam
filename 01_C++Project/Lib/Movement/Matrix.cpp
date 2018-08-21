#include "stdafx.h"
#include "Matrix.h"
#include <math.h>

Matrix31::Matrix31()
{
	matrix[0] = matrix[1] = 0;
	matrix[2] = 1;
}

Matrix31::Matrix31(float x, float y)
{
	matrix[0] = x;
	matrix[1] = y;
	matrix[2] = 1;
}

Matrix33::Matrix33()
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			// matrix 모두 0으로 채우기
			matrix[y][x] = 0;
			// 대각선 1로 채우기
			if (y == x)
			{
				matrix[y][x] = 1;
			}
		}
	}
}

float Matrix31::GetX()
{
	return matrix[0];
}

float Matrix31::GetY()
{
	return matrix[1];
}

// 평행이동 매트릭스
void Matrix33::ParallelMoveMent(float dx, float dy)
{
	matrix[2][0] = dx;
	matrix[2][1] = dy;
}

void Matrix33::RotationMovement(float degree)	// 회전용 매트릭스로 만듦(인수는 degree)
{
	// 우리가 받은 값은 degree(360도) 단위지만, 라이브러리 삼각함수에서
	// 받는 값은 라디안(2pi)값이다.
	// 그러므로 여기서 degree를 radian으로 바꾸어 입력해야 한다.
	// 그러기 위해서는 degree를 pi / 180으로 곱해야 한다.
	float Cos = cos(degree * pi / 180);
	float Sin = sin(degree * pi / 180);
	matrix[0][0] = Cos;
	matrix[1][0] = -Sin;
	matrix[0][1] = Sin;
	matrix[1][1] = Cos;
}

void Matrix33::ParallelMovement(float dx, float dy)
{
	// 2차원 배열 첨자를 사용할 때 보통 matrix[row][colum]을
	// 사용하지만, 첨자의 규칙을 확실하게 정한다면 다른
	// 형식의 첨자체계를 사용할 수 있다.
	// 여기서는 행렬의 X, Y좌표에 맞춰 배열을 matrix[x][y]로
	// 정한다.

	matrix[2][0] = dx;
	matrix[2][1] = dy;
}

Matrix31 Matrix33::operator *(Matrix31 &matrix31)
{
	Matrix31 result;

	for (int resultSlot = 0; resultSlot < 3; ++resultSlot)
	{
		for (int idx = 0; idx < 3; ++idx)
		{
			result.matrix[resultSlot] += this->matrix[idx][resultSlot] * matrix31.matrix[idx];
		}
	}
	return result;
}

Matrix33 Matrix33::operator *(Matrix33 &matrix33)
{
	Matrix33 result;
	for (int resultX = 0; resultX < 3; ++resultX)
	{
		for (int resultY = 0; resultY < 3; ++resultY)
		{
			result.matrix[resultX][resultY] = 0;
			for (int index = 0; index < 3; ++index)
			{
				result.matrix[resultX][resultY] +=
					this->matrix[index][resultY] *
					matrix33.matrix[resultX][index];
			}
		}
	}
	return result;
}