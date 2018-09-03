#pragma once
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

const int mizeSize = 10;	// 미로 사이즈
// 셀안은 비어있거나 장애물이 있다.
enum CellType { EmptyCell, Obstacle};
class Coord;
class Mize	// 미로를 관리할 객체
{
private:
	CellType cell[mizeSize][mizeSize];

public:
	Mize();
	bool CanEntry(Coord coords);	// 좌표 안에 들어갈 수 있는가?

	void Print()
	{
		for (int y = 0; y < mizeSize; ++y)
		{
			for (int x = 0; x < mizeSize; ++x)
			{
				cout << (cell[x][y] == EmptyCell ? " ." : " #");
			}
			cout << endl;
		}
	}
};

class Coord	// 미로 상에 위치를 나타내는 좌표
{
public:
	int x, y;
	Coord(int x, int y);
};

class UnitMove	// 미로 안에 한칸 이동하는 사건의 객체
{
public:
	Coord locate;	// 현재 위치
	Coord from;		// 이동 방향
	float distFromStart;	// 길찾기 시작한 위치로부터의 거리
	UnitMove(Coord from, Coord goal, float distFromStart);
};

class Monster
{
private:
	Coord locate;	// 현재 위치
	void PathFind(Mize &mize, Coord from, Coord goal);	// 길찾기 함수
	// 현재 위치 부터, 끝나는 위치
public:
	Monster(int x, int y);	//생성자
	void PathFind(Mize &mize, int goalX, int goalY);	// 목적지 설정 함수
};

// 길찾기 시 오픈리스트와 클로즈 리스트를 모두 관리하기 위한 객체
class UnitMoveList : public list<UnitMove>
{
public:
	// 이 리스트 안에 nextCell이 있는지 확인하기 위한 메서드
	bool IsInList(Coord &nextCell)
	{
		// this의 리스트 안에서 nextCell과 일치하는 unitMove가 있는지 확인한다.

		iterator fnd = find_if(begin(), end(),
			[&nextCell](UnitMove &unitMove)->bool
		{
			if (unitMove.locate.x == nextCell.x &&
				unitMove.locate.y == nextCell.y)
				return true;
			return false;
		});
		if (fnd == end())	// 못 찾았다!!
			return false;
		return true;
	}

	void TotalPath(UnitMove goal)
	{
		list<Coord> path;
		while (true)
		{
			path.push_front(goal.locate);

			// 최초 시작점은 from과 locate를 같이 넣었으므로, 이 둘이 같다는 것은
			// 최초 위치 가지 도달했다는 것
			if (goal.from.x == goal.locate.x && goal.from.y == goal.locate.y)
			{
				// 패스 출력
				for (list<Coord>::iterator crd = path.begin(); crd != path.end(); ++crd)
				{
					cout << crd->x << "," << crd->y << endl;
				}
				return;
			}
			// goal은 goal.from에서 왔으므로 리스트에서 goal.from을 찾아야 한다.
			iterator fnd = find_if(begin(), end(),
				[&goal](UnitMove &unitMove)->bool
			{
				if (unitMove.locate.x == goal.from.x &&
					unitMove.locate.y == goal.from.y)
					return true;
				return false;
			});

			if (fnd == end())
			{
				cout << "길이 중간에서 끊겼다.!!";
				return;
			}
			goal = *fnd;	//goal의 위치를 fnd로 바꿈
		}
	}

	UnitMove ShortestPath()
	{
		// 1. 첫 번째 객체를 가장 짧은 경로라 가정한다.
		iterator shotest = begin();

		// 2. 다른 객체들과 비교해서 더 짧은 것이 있으면 그것을 가장 짧은 것으로 가정
		for (iterator cell = begin();
			// vector가 아니라 list이므로
			// cell = begin() + 1; 식 사용 불가
			cell != end(); ++cell)
		{
			if (shotest->distFromStart > cell->distFromStart)
				shotest = cell;
		}

		// 3. 여기까지 오면 shortest에는 가장 짧은 경로가 들어오게 된다.
		UnitMove rtnValue = *shotest;
		erase(shotest);
		return rtnValue;
	}
};
