#include "stdafx.h"
#include "Matrix.h"

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

void Matrix33::ParallelMoveMent(float dx, float dy)
{
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