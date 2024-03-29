#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
using namespace System;

class ComplexNumber
{
public:
	float real;
	float img;
public:
	ComplexNumber()
	{
		real = img = 0;
	}
};

class DynamicArray
{
private:
	int *array;
public:
	DynamicArray()
	{
		array = new int[10];
	}
	/*
	동적할당을 하는 클래스에서는 그냥 복사를 하게되면 동적할돵된
	포인터 변수까지 복사가 되기 때문에 한번 할당된 메모리를 두번 반환하는
	결과가 나올 수 있다. 그러므로 복사생성자를 만들어 별개의 메모리를 할당을
	하도록 만들어야 한다.
	복사생성자 객체를 =(대입 연산자)를 통해 복사할 때 호출
	*/
	DynamicArray(const DynamicArray &da)
	{
		array = new int[10];
		for (int index = 0; index < 10; ++index)
			array[index] = da.array[index];
	}
	// 대입연산자 오버로드
	void operator =(const DynamicArray &da)
	{
		/*
		대입 연사자가 실행되었다는 것은, 이미 객체가 만들어진 후 대입연산이
		일어났다는 뜻. 그러므로 새로 할당하기 전에 기존 동적할당 반납
		*/
		delete[] array;
		array = new int[10];
	}
	~DynamicArray()
	{
		delete[] array;
	}
};

//반환값 opertor <<(인수)
ostream &operator << (ostream &cout, ComplexNumber & cn)
{
	cout << cn.real << '+' << cn.img << 'i';
	return cout;
}

template<typename I, typename V>
class ObjectContainer
{
private:
	I index;
	V value;
public:
	ObjectContainer(I index, V value);
	void Write();
};

template<typename I, typename V>
ObjectContainer<I, V>::ObjectContainer(I index, V value)
{
	this->index = index;
	this->value = value;
}

template<typename I, typename V>
void ObjectContainer<I, V>::Write()
{
	cout << index << ":" << value << endl;
}

int main()
{
	ObjectContainer<int, string> intString(1, "First");
	ObjectContainer<string, double> strDbl("PI", 3.14);
	ObjectContainer<short, string> shortDbl(1, "one");
	intString.Write();
	strDbl.Write();
	shortDbl.Write();

	ObjectContainer<string, ComplexNumber> strCmp("ComplexNumber", ComplexNumber());
	// complexNumber()은 임시객체로, 여기서 임시로 객체가 만들어진 후
	// 해당 메서드(여기서는 strCmp의 생성자)로 전달된 후 즉시 사라진다.
	// 물론 이때 생성자, 소멸자가 실행된다.
	strCmp.Write();
	ObjectContainer<int, DynamicArray> intDA(1, DynamicArray());
    return 0;
}
