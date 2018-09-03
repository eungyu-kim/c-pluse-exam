#pragma once
#include <iostream>
#include <list>
using namespace std;

const int mizeSize = 10;	// 미로 사이즈
// 셀안은 비어있거나 장애물이 있다.
enum CellType { EmptyCell, obstacle};	
class Mize	// 미로를 관리할 객체
{
private:
	CellType cell[mizeSize][mizeSize];

public:
	Mize();
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
	UnitMove(Coord from, Coord goal);
};

class Monster
{
private:
	Coord locate;	// 현재 위치
	void PathFind(Coord from, Coord goal);	// 길찾기 함수
	// 현재 위치 부터, 끝나는 위치
public:
	Monster(int x, int y);	//생성자
	void PathFind(int goalX, int goalY);	// 목적지 설정 함수
};