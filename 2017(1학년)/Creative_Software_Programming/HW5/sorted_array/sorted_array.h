#ifndef sorted_array
#define	sorted_array
#include<vector>
#include<iostream>

using namespace std;
class SortedArray{
public:
	SortedArray();
	   ~SortedArray();
	   void AddNumber(int num);
	   vector<int> GetSortedAscending();
	   vector<int> GetSortedDescending();
	   int GetMax() const;
	   int GetMin() const;
private:
	vector<int> numbers_;
};

#endif
