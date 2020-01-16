#include "simple_int_set.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>

using namespace std;
void SimpleIntSet::sortElements()
{
	sort(mElements, mElements + mElementCount);
}

SimpleIntSet::SimpleIntSet()
{
	mElements = new int[MAX_SIZE];
	mElementCount = 0;
	set<int> arr;
	set<int> arr2;
	vector<int> result;
}

SimpleIntSet::SimpleIntSet(int * _elements, int _count)
{
	for (int i = 0; i < _count; ++i) {
		arr.insert(_elements[i]);
	}
	/*mElements = new int[_count];
	for (int i = 0; i < _count; i++) {
		mElements[i] = _elements[i];
	}*/
	mElementCount = _count;
}

SimpleIntSet::~SimpleIntSet()
{
}

set<int> SimpleIntSet::elements() const
{
	return arr;
}

int SimpleIntSet::elementCount() const
{
	return mElementCount;
}

set<int> SimpleIntSet::SetIntersection(const set<int>& set0, const set<int>& set1)
{
	result.resize(set0.size() + set1.size());
	vector<int>::iterator itr = set_intersection(set0.begin(), set0.end(), set1.begin(), set1.end(),result.begin());
	result.erase(itr, result.end());
	for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
		arr2.insert(*it);
	}
	//for (set<int>::iterator it = arr2.begin(); it != arr2.end(); it++) {
		//cout << *it << ' ';
	//}
	return arr2;
}
set<int> SimpleIntSet::SetUnion(const set<int>& set0, const set<int>& set1)
{
	result.resize(set0.size() + set1.size());
	vector<int>::iterator itr = set_union(set0.begin(), set0.end(), set1.begin(), set1.end(), result.begin());
	result.erase(itr, result.end());
	for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
		arr2.insert(*it);
	}
	return arr2;
}
set<int> SimpleIntSet::SetDifference(const set<int>& set0, const set<int>& set1)
{
	result.resize(set0.size() + set1.size());
	vector<int>::iterator itr = set_difference(set0.begin(), set0.end(), set1.begin(), set1.end(), result.begin());
	result.erase(itr, result.end());
	for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
		arr2.insert(*it);
	}
	return arr2;
}
void SimpleIntSet::printSet()
{
	cout << "{" << ' ';
	for (set<int>::iterator it3 = arr2.begin(); it3 != arr2.end(); it3++) {
		cout << *it3<<' ';
	}
	cout << "}" << endl;
}