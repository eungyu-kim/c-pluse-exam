#include "stdafx.h"
#include "DefenceObject.h"

///////////////////////
// 생성자
///////////////////////

BaseObject::BaseObject(float locX, float height, float degree, float speed)
	:velocity(degree, speed)
{
	this->locX = locX;
	this->height = height;
	this->behavior = nullptr;
	this->lastMoveTime = timeGetTime();		// 최초 만들어진 시간
}

BaseObject::~BaseObject()
{
	if (behavior != nullptr)
		delete behavior;
}

Matrix31 Airplain::lines[3][2];
bool Airplain::initializeComplate;
Airplain::Airplain(float height)	// 베이스 클래스 생성자 호출
	: BaseObject(0, height, 90, airplainSpeedPerSec)
{
	behavior = new UniformMoving();		// 비행기는 등속운동하는 움직임을 동적할당
	if (initializeComplate == false)
	{
		float half = airplainSize;
		// 진행방향 0도(위로 곧추 선) 비행기
		// velocity 방향으로 회전시켰을 때 제대로 된 모습이 나온다.
		lines[0][0] = Matrix31(0, -half);
		lines[0][1] = Matrix31(0, half);

		lines[1][0] = Matrix31(-half / 2, 0);
		lines[1][1] = Matrix31(half / 2, 0);

		lines[2][0] = Matrix31(-half / 4, half);
		lines[2][1] = Matrix31(half / 4, half);

		initializeComplate = true;
	}
}

ObjList::ObjList()
{
	regenRate = 20;
}

Matrix31 Bomb::lines[4][2];
bool Bomb::initializeComplete = false;
Bomb::Bomb(float locX, float height)
	: BaseObject(locX, height, 90, airplainSpeedPerSec)
{
	behavior = new FallByGravity();		// 중력에 의해 떨어짐
	if (initializeComplete == false)
	{
		float half = bombSize;
		lines[0][0] = Matrix31(half / 2, half);
		lines[0][1] = Matrix31(-half / 2, -half / 3);

		lines[1][0] = Matrix31(-half / 2, -half / 3);
		lines[1][1] = Matrix31(0, -half);

		lines[2][0] = Matrix31(-half / 2, half);
		lines[2][1] = Matrix31(half / 2, -half / 3);

		lines[3][0] = Matrix31(half / 2, -half / 3);
		lines[3][1] = Matrix31(0, -half);

		initializeComplete = true;
	}
}



/////////////////////////////
// 비행기 리젠
/////////////////////////////
void ObjList::AirplainRegen()
{
	// 처음엔 조금씩 나오다가 점점 많이 나오도록
	if (rand() % 100 < regenRate)		// 20% 확률
	{
		float halfField = fieldHeight / 2;
		// 비행기 리젠
		float height = rand() % (int)halfField + halfField;
		push_back(new Airplain(height));
		//this는 생략 가능하다.
	}
	++regenRate;
}

//진행 방향으로 회전하고 평행이동하는 매트릭스
Matrix33 BaseObject::TranslateMatrix()
{
	// 진행 방향으로 회전시키는 매트릭스
	Matrix33 rotate;
	rotate.RotationMovement(velocity.GetDegree());

	// 현재 위치로 평행이동시키는 매트릭스
	Matrix33 parallel;
	float locY = fieldHeight - height;
	parallel.ParallelMovement(locX, locY);

	//회전하고 이동한다.
	return parallel * rotate;
}

/////////////////////////////
// 그리기
/////////////////////////////
void Airplain::Draw(HDC hdc)
{
	// 베이스인 BaseObject에서 만든 변환 매트릭스로
	// 좌표를 변환해서 그리기
	Matrix33 translate = TranslateMatrix();
	for (int ln = 0; ln < 3; ++ln)
	{
		Matrix31 move = translate * lines[ln][0];
		Matrix31 line = translate * lines[ln][1];

		MoveToEx(hdc, move.GetX(), move.GetY(), nullptr);
		LineTo(hdc, line.GetX(), line.GetY());
	}
}

void Bomb::Draw(HDC hdc)
{
	Matrix33 translate = TranslateMatrix();
	for (int ln = 0; ln < 4; ++ln)
	{
		Matrix31 move = translate * lines[ln][0];
		Matrix31 line = translate * lines[ln][1];

		MoveToEx(hdc, move.GetX(), move.GetY(), nullptr);
		LineTo(hdc, line.GetX(), line.GetY());
	}
}

void ObjList::Draw(HDC hdc)
{
	// 여기가 이미 ObjList안 이므로 ObjList::iterator에서
	// ObjList::를 생략할 수 있다.
	// 또한 objList.begin()에서도 여기가 objList객체
	// 안이므로 그냥 begin(), end()로 사용 가능
	for (iterator obj = begin(); obj != end(); ++obj)
	{
		(*obj)->Draw(hdc);
	}
}

///////////////////////////////////////
// 움직임
//////////////////////////////////////
void UniformMoving::Move(Vector &velocity, float interval, float &locX, float &height)
{
	// velocity의 속도로 등속운동을 해서 그 결과를 locX, height로 전달하는 함수

	// 1. velocity를 x, y축으로 나우어 dx와 dy로 나눈다.
	float dx, dy;
	velocity.DeltaXY(dx, dy);

	// 2. 등속 운동 변화 위치 * dealtaTime
	locX += dx * interval;
	height -= dy * interval;


}

void FallByGravity::Move(Vector &velocity, float interval, float &locX, float &height)
{
	// 이 오브젝트에 적용된 중력 벡터 만들기
	Vector gravity(180,						// 무조건 땅을 향해 작용하므로 각도는 180
		gravityAccelerate * interval);		// interval 시간만큼 작용했으므로
	velocity += gravity;		// 원래 속도에 interval 시간 만큼 작용한 중력 적용
								// interval 만큼 시간이 지났을 때의 오브젝트의 속도

	// 이후에 새로운 velocity로 이동한 거리 계산
	// 그 계산은 UniformMoving과 동일하므로
	UniformMoving::Move(velocity, interval, locX, height);
}


////////////////////////////////////
// 루틴
////////////////////////////////////

void BaseObject::Routine(ObjList & objList)
{
	// 지난번 Routine 또는 만들어진 때부터의 시간
	long curTime = timeGetTime();
	float interval = (curTime - lastMoveTime) / 1000.0;

	// 움직인다.
	// interval과 velocity로 새로운 위치 계산
	// Behavior 계통의 다른 객체를 이용할 것이므로
	if (behavior != nullptr)
	{
		behavior->Move(velocity, interval, locX, height);
	}
	// 여기 BaseObject::Routine()에서 하는 행동은 모든 오브젝트의
	// 공통된 행동(이동)이다.
	// 하지만 오브젝트마다 다른 행동을 할 수 있으며, 그 행동은
	// 오브젝트마다 재정의해서 사용되어야 한다.

	// 그 밖의 다른 행동
	OtherRoutine(objList);		// 각 오브젝트들마다 특별하게 해야 할 행동


	lastMoveTime = curTime;
}

void ObjList::Routine()
{
	for (iterator obj = begin(); obj != end(); ++obj)
	{
		(*obj)->Routine(*this);
		// 이 반복자를 이용한 반복문 안에서 만들어진
		// Bomb은 reserve리스트에 보관되어 있음
	}
	// 반복자의 반복이 끝난 후에 reserve에 있는
	// Bomb들을 리스트에 추가
	for (iterator resv = reserve.begin(); resv != reserve.end(); ++resv)
	{
		push_back(*resv);
	}
	// 리스트에 있는 것 다 추가했으므로 리스트 지움
	reserve.clear();
}

void BaseObject::OtherRoutine(ObjList & objList)
{

}

void Airplain::OtherRoutine(ObjList & objList)
{
	// 폭탄 떨구기
	if (rand() % 100 < bombDropRate)
	{
		//폭타탄을 만든다.
		// 그러나 이 메서드는 ObjList::Routine에서 반복자를 돌리는 동안 호출된 것이므로 
		// 여기서 직접 오브젝트를 추가하면 반복자가 파괴될 위험성 있음
		//objList.push_back(new Bomb(locX, height));

		// 직접 추가하는 것이 아니라 다른 리스트에 추가했다가
		// 나중에 한번에 리스트에 넣는 것이 좋음
		objList.PushBackReserve(new Bomb(locX, height));
		// 지금 당장 넣지 말고 예약을 할 것
	}
}

void ObjList::PushBackReserve(BaseObject *obj)
{
	reserve.push_back(obj);
}
