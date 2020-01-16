#include <iostream>
#include <stdlib.h>
#include<string>
#include "simple_int_set.h"
using namespace std;
enum EOperateType
{
	Invalid = -1,

	Add,
	Sub,
	Mul,
	Print,
};
typedef enum EOperateType OperateType;
int main(void)
{
	while (true)
	{
		string inputs;
		getline(cin, inputs);

		if (inputs == "0") break;

		string *argv = new string[inputs.length()]; // more than count
		string token;
		size_t pos;
		int argc = 0;

		while (true)
		{
			pos = inputs.find(' ');
			token = inputs.substr(0, pos);

			argv[argc++] = token;

			if (pos >= inputs.length()) break;
			else inputs.erase(0, pos + 1);
		}

		SimpleIntSet *left = NULL;
		SimpleIntSet *right = NULL;

		int *elements = NULL;
		int elementCount = 0;
		OperateType type = Invalid;

		for (int i = 0; i<argc; ++i)
		{
			string arg = argv[i];
			if (arg == "{" && elements == NULL) elements = new int[argc];
			else if (isdigit(arg[arg.length() - 1])) elements[elementCount++] = atoi(arg.c_str());

			else if (arg == "}")
			{
				SimpleIntSet *newSet = new SimpleIntSet(elements, elementCount);
				if (left == NULL) left = newSet;
				else if (right == NULL) right = newSet;

				delete elements;
				elements = NULL;
				elementCount = 0;
				if (type == Invalid) type = Print;
			}
			else if (arg == "+") type = Add;
			else if (arg == "-") type = Sub;
			else if (arg == "*") type = Mul;
		}

		switch (type)
		{
		case Add:
			left->SetUnion(left->arr,right->arr); break;
		case Sub:
			left->SetDifference(left->arr, right->arr); break;
		case Mul:
			left->SetIntersection(left->arr, right->arr); break;
		default: break;
		}
		if (type != Invalid) left->printSet();

		left->arr.clear();
		right->arr.clear();
		delete left;
		delete right;
	}
	return 0;
}