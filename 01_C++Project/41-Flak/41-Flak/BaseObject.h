#pragma once
class BaseObject
{
protected:
	float locX;
	float locY;
	BaseObject(float locX, float locY);

public:
	virtual void Draw(HDC hdc) = 0;
};