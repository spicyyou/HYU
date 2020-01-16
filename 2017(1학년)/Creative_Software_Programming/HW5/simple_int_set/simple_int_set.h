// simple_int_set.h
// Implement your simple_int_set.cc
#include<set>
#include<vector>
using namespace std;
#ifndef __hw03__simple_int_set__
#define __hw03__simple_int_set__

#define MAX_SIZE 1024

class SimpleIntSet
{
private:
    int *mElements;
    int mElementCount;

    void sortElements(); // you can reuse your previous sort assignment
    SimpleIntSet();
    
public:
	set<int> arr;
	vector<int> result;
	set<int> arr2;
    SimpleIntSet(int *_elements, int _count);
    ~SimpleIntSet();
    
    set<int> elements() const; // return sorted array
    int elementCount() const;
    
	set<int> SetIntersection(const set<int>& set0, const set<int>& set1);
	set<int> SetUnion(const set<int>& set0, const set<int>& set1);
	set<int> SetDifference(const set<int>& set0, const set<int>& set1);
   /*impleIntSet *unionSet(SimpleIntSet& _operand);
    SimpleIntSet *differenceSet(SimpleIntSet& _operand);
    SimpleIntSet *intersectSet(SimpleIntSet& _operand);*/
    
    void printSet();
};

#endif
