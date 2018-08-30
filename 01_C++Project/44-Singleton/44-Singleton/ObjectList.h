// ObjectList.h
#pragma once
#include <vector>
#include <iostream>
using namespace std;

class IntList : public vector<int>
{
	static IntList intList;
private:
	IntList()
	{

	}
	IntList(const IntList &)
	{

	}
public:
	static IntList &GetIntList()
	{
		return intList;
	}
};

class IntListUser
{
public:
	void PushBack(int val);
	void Write(IntList &intList);
};