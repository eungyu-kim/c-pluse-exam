#include "stdafx.h"
#include "Mize.h"
using namespace System;

int main()
{
	Mize mize;	// 미로 객체를 만든다.
	mize.Print();

	Monster monster(0, 0);	// (0, 0)에 몬스터 생성
	monster.PathFind(mize, mizeSize - 1, mizeSize - 1);
    return 0;
}
