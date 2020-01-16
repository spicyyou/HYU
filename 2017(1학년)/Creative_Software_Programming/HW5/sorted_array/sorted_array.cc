#include "sorted_array.h"

#include <iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

SortedArray::SortedArray()
{
	vector<int> numbers_;
}

SortedArray::~SortedArray()
{
}

void SortedArray::AddNumber(int num)
{
	numbers_.push_back(num);
}

vector<int> SortedArray::GetSortedAscending()
{
	sort(numbers_.begin(), numbers_.end());
	for (int i = 0; i < numbers_.size(); i++) {
		cout << numbers_[i]<<' ';
	}
	cout << endl;
	return vector<int>();
}

vector<int> SortedArray::GetSortedDescending()
{
	sort(numbers_.begin(), numbers_.end(), greater<int>());
	for (int i = 0; i < numbers_.size(); i++) {
		cout << numbers_[i] << ' ';
	}
	cout << endl;
	return vector<int>();
}

int SortedArray::GetMax() const
{
	int max = 0;
	for (int i = 0; i < numbers_.size(); i++) {
		if (max < numbers_[i])
			max = numbers_[i];
	}
	return max;
}

int SortedArray::GetMin() const
{
	int min = 100000000000;
	for (int i = 0; i < numbers_.size(); i++) {
		if(min > numbers_[i])
			min = numbers_[i];
	}return min;
}
