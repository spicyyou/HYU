#include "simple_int_set.h"
#include<algorithm>
#include<iostream>

using namespace std;
void SimpleIntSet::sortElements()
{
	sort(mElements, mElements + mElementCount);
}

SimpleIntSet::SimpleIntSet()
{
	mElements = new int[MAX_SIZE];
	mElementCount = 0;
}

SimpleIntSet::SimpleIntSet(int * _elements, int _count)
{
	mElements = new int[_count];
	for (int i = 0; i < _count; i++) {
		mElements[i] = _elements[i];
	}
	mElementCount = _count;
	sortElements();
}

SimpleIntSet::~SimpleIntSet()
{
}

int * SimpleIntSet::elements() const
{
	return mElements;
}

int SimpleIntSet::elementCount() const
{
	return mElementCount;
}

SimpleIntSet * SimpleIntSet::unionSet(SimpleIntSet & _operand)
{	//mElement는 왼쪽(left)
	//_operand가 오른쪽 배열인데 왼쪽배열에 없는것을 오른쪽배열에 찾아서 left에 넣어주면 됨
	int cnt = 0;
	int arr[MAX_SIZE] = { 0, };

	for (int i = 0; i < mElementCount;i++) {
		arr[i] = elements()[i];
	}
	for (int i = 0; i < _operand.mElementCount; i++) {
		for (int j = 0; j < mElementCount; j++) {
			if (mElements[j] != _operand.mElements[i])
				cnt++;
		}
		if (cnt == mElementCount) {
			arr[mElementCount++] = _operand.mElements[i];
		}
		cnt = 0;
	}
	mElements = arr;
	sortElements();//합집합 정렬되서 나와야하나?
	return this;
}
//차집합
SimpleIntSet * SimpleIntSet::differenceSet(SimpleIntSet & _operand)
{

	int arr[MAX_SIZE] = { 0, };
	int cnt = 0;
	int num = 0;
	for (int i = 0; i < mElementCount; i++) {
		for (int j = 0; j < _operand.mElementCount; j++) {
			if (mElements[i] != _operand.mElements[j]) {
				cnt++;
			}
		}
		if (cnt == _operand.mElementCount) {
			arr[num++] = mElements[i];
		}
		cnt = 0;
	}
	mElementCount = num;
	mElements = arr;
	return this;
}

SimpleIntSet * SimpleIntSet::intersectSet(SimpleIntSet & _operand)
{
	int new_Elements[MAX_SIZE]={ 0, };
	int cnt = 0;
	for (int i = 0; i < elementCount(); i++) {
		for (int j = 0; j < _operand.elementCount(); j++) {
			if (mElements[i] == _operand.mElements[j]) {
				new_Elements[cnt++]= mElements[i];
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		mElements[i] = new_Elements[i];
	}
	mElementCount = cnt;
	sortElements();
	return this;
}

void SimpleIntSet::printSet()
{
	cout << "{ ";
	for (int i = 0; i < elementCount(); i++) {
		cout << mElements[i]<<" ";
	}
	cout << "}" << endl;
}