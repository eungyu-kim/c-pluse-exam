//Mize.cpp
#include "stdafx.h"
#include "Mize.h"

Mize::Mize() // 미로 생성자
{	// 미로 전체에 장애물이 하나도 업도록 생성
	for (int y = 0; y < mizeSize; ++y)
	{
		for (int x = 0; x < mizeSize; ++x)
		{
			cell[y][x] = EmptyCell;
		}
	}
}

Coord::Coord(int x, int y)	// 좌표 x, y설정 생성자
{
	this->x = x;
	this->y = y;
}

Monster::Monster(int x, int y)	// 몬스터 위치 설정 생성자
	: locate(x, y)
{

}

UnitMove::UnitMove(Coord locate, Coord from)
	: locate(locate), from(from)
{
}

void Monster::PathFind(Mize &mize, int goalX, int goalY)	// 목표 위치 설정
{
	PathFind(mize, locate, Coord(goalX, goalY));	// 현재 위치 -> 목표 위치 탐색
}

void Monster::PathFind(Mize &mize,Coord from, Coord goal) // 현재 위치 -> 목표 위치 탐색
{
	list<UnitMove> openList;	// 앞으로 갈 수 있는 영역
	list<UnitMove> closeList;	// 이미 이동한 영역

	// 1. 몬스터의 현재 위치 앞으로 갈 수 있는 영역으로 저장
	openList.push_back(UnitMove(from, from));

	while (true)
	{
		UnitMove cell = openList.front();	// 저장 위치 중 맨 앞을 꺼낸다.
		openList.erase(openList.begin());	// 리스트의 최초 객체 제거

		for (int dy = -1; dy <= 1; ++dy)
		{
			for (int dx = -1; dx <= 1; ++dx)
			{
				// dy와 dx는 0이 아닌 위치
				if (dy != 0 || dy != 0)
				{
					// 현재 위치(x,y) x + dx , y + dy 
					Coord nextCell(cell.locate.x + dx, cell.locate.y + dy);

					if (!mize.CanEntry(nextCell))
					{
						continue;
					}

					list<UnitMove>::iterator fnd =
						find_if(closeList.begin(), closeList.end(),
							// 찾을 객체 람다식으로 정의
							[&nextCell](UnitMove &unitMove)->bool
					{
						if (unitMove.locate.x == nextCell.x &&
							unitMove.locate.y == nextCell.y)
							return true;
						return false;
					});

					if (fnd != closeList.end())
					{
						continue;
					}
				}
			}
		}
	}
}

bool::Mize::CanEntry(Coord coords)
{
	// (x, y)로 들어갈 수 있느냐는 그 위치의 셀이 비어있느냐는 뜻
	int x = coords.x;
	int y = coords.y;

	// 미로 영역 밖으로 나갈 수는 없다.
	if (x < 0 || x >= mizeSize)
		return false;
	if (y < 0 || y >= mizeSize)
		return false;

	if (cell[x][y] == EmptyCell)
		return true;
	return false;
}