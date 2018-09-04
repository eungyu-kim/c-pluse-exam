// for-each-1.cpp : 기본 프로젝트 파일입니다.
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace System;

class IntClass
{
private:
	int value;
public:
	IntClass(int value)
	{
		this->value = value;
	}
	void Write()
	{
		cout << value << endl;
	}
};
int main()
{
	vector<IntClass> intVector;

	intVector.push_back(IntClass(4));
	intVector.push_back(IntClass(5));
	intVector.push_back(IntClass(3));
	intVector.push_back(IntClass(2));

	cout << "일반적인 사용" << endl;
	for each(IntClass ic in intVector)
	{
		ic.Write();
	}
	cout << endl;
	return 0;
}
