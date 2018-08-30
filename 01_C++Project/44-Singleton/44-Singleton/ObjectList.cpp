// ObjectList.cpp
#include "stdafx.h"
#include "ObjectList.h"

IntList IntList::intList;
void IntListUser::PushBack(int val)
{
	//IntList intList;
	IntList::GetIntList().push_back(val);
}
void IntListUser::Write(IntList &intList)
{
	for (IntList::iterator num = IntList::GetIntList().begin();
		num != IntList::GetIntList().end(); ++num)
	{
		cout << *num << endl;
	}
}