#pragma once
#include "BaseObject.h"
#include "Matrix.h"
class Flak : public BaseObject
{
private:
	Matrix31 lines[5][2];

public:
	Flak();
};