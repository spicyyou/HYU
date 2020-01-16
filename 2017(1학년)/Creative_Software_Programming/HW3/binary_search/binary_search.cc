#include "binary_search.h"
#include <algorithm>
using namespace std;
void BinarySearch::sortArray()
{
	sort(mArray, mArray + mArrayCount);
}

BinarySearch::BinarySearch()
{
	mArray=new int [mArrayCount];
}

BinarySearch::BinarySearch(int * _array, int _arrayCount)
{
	mArrayCount = _arrayCount;
	mArray = new int[mArrayCount];
	for (int i = 0; i < mArrayCount; i++) {
		mArray[i] = _array[i];
	}
	sortArray();
}

BinarySearch::~BinarySearch()
{
}

int BinarySearch::getIndex(int _element)
{
	int start=0, end=mArrayCount-1;
	int mid;
	while (start <= end) {
		mid = (start + end) / 2;
		if (_element == mArray[mid]) return mid;
		else if (_element > mArray[mid]) {
			start = mid+1;
		}
		else if (_element < mArray[mid]) {
			end = mid-1;
		}
	}
	return -1;
}
