#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;
using namespace System;

int main()
{
	map<int, string> fruit;

	fruit.insert(pair<int, string>(1, "사과"));
	fruit[2] = "포도";
	fruit[5] = "배";

	for (map<int, string>::iterator fru = fruit.begin();
		fru != fruit.end();
		++fru)
	{
		cout << fru->first << " : " << fru->second << endl;
	}

	cout << "키 값을 입력해 주세요";
	int key;
	cin >> key;

	if (fruit.find(key) != fruit.end())
	{
		cout << key << "번 과일은 " << fruit[key] << endl;
		cout << endl;
		cout << key << "번 과일 제거" << endl;
		fruit.erase(key);
	}

	for (map<int, string>::iterator fru = fruit.begin();
		fru != fruit.end();
		++fru)
	{
		cout << fru->first << " : " << fru->second << endl;
	}
    return 0;
}
