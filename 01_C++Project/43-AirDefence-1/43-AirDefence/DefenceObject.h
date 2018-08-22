#pragma once
#include "../../Lib/Movement/Vector.h"
#include "../../Lib/Movement/Matrix.h"
#include <list>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")	// timeGetTime() 함수가 포함되어 있는 라이브러리
#include <stdlib.h>					// rand()를 사용하기 위한 헤더

// 게임에 나오는 상수 모음
const float fieldWidth = 1000;					// 화면 넓이
const float fieldHeight = 800;					// 화면 높이

const float airplainSpeedPerSec = 100;			// 비행기 초속
const float airplainSize = 50;					// 비행기 크기

// 타이머 세팅
const int Timer_AirplainRegen_ID = 1;			// 비행기 생성 ID
const int Timer_AirplainRegen_Interval = 1000;	// 1초 간격으로 생성

const int Timer_ObjectRoutine_ID = 2;			// 이번에 각 오브젝트들이 해야할 일
const int Timer_ObjectRoutine_Interval = 50;

class Behavior;
class ObjList;

class BaseObject
{
protected:
	float locX;			// 화면 왼쪽 끝에서 부터의 위치
	float height;		// 오브젝트의 고도 - 화면 아래쪽부터의 위치
	Vector velocity;		// 속도
	long lastMoveTime;	// 마지막으로 이동한 시간
	Behavior *behavior;	// 이 오브젝트의 움직임을 관리한다.
	BaseObject(float locX, float height, float degree, float speed);
	

	// 오브젝트들을 그리기 위해 좌표를 변환할 매트릭스를 만드는 메서드
	Matrix33 TranslateMatrix();

public:
	virtual void Draw(HDC hdc) = 0;
	virtual ~BaseObject();
	// 1. 소멸자는 어디서 호출될지 모르므로 항상
	//		public이 되어야 한다.
	// 2. BaseObject에서 상속된 클래스의 소멸자도
	//		같이 실행하기 위해서는 가상함수로 만들어야 한다.

	void Routine(ObjList & objList);	//행동
};


class Airplain : public BaseObject
{
private:
	static Matrix31 lines[3][2];		// 선 세개로 완료
	static bool initializeComplate;

public:
	Airplain(float height);
	void Draw(HDC hdc) override;
};

class ObjList : public std::list<BaseObject *>
{
private:
	int regenRate;					// 리젠될 확률
	std::list<BaseObject *> reserve;
public:
	ObjList();

	void AirplainRegen();
	void Draw(HDC hdc);
	void Routine();
};

// 게임에 나오는 모든 오브젝트들의 움직임을 관리하는 클래스
// 만약 비행기의 움직임이라면, 
// behavior에서 상속 받은 UniformMoveing이 관리한다.
class Behavior
{
public:
	virtual void Move(Vector &velocity, float interval, float &locX, float &height) = 0;
	// velocity는 객체이며 
	// 상황에 따라 값이 바뀔 수 있으므로
	// loCX, height도 오브젝으틔 바뀐 값을 받아야 하므로
	// 참조형 필요
};
class UniformMoving : public Behavior
{
	// 오브젝트를 등속운동하게 만드는 객체
public:
	void Move(Vector &velocity, float interval, float &locX, float &height) override;
};