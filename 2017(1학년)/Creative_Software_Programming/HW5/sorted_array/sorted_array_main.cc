#include "sorted_array.h"
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

int main() {
	SortedArray sortedarray;
	string inputs;
	int arr_num = 0;
	int j = 0;
	while (1) {
		string command;
		getline(cin, command);
		if (command == "ascend") {
			sortedarray.GetSortedAscending();
		}
		else if (command == "descend") {
			sortedarray.GetSortedDescending();
		}
		else if (command == "max") {
			cout << sortedarray.GetMax() << endl;
		}
		else if (command == "min") {
			cout<<sortedarray.GetMin()<<endl;
		}
		else if (command == "quit") {
			break;//전체 while문으로 넣기
		}
		else {
			while (1) {
				size_t pos2 = command.find(' ');
				string token2 = command.substr(0, pos2);
				size_t num2 = atoi(token2.c_str());
				sortedarray.AddNumber(num2);
				j++;
				if (pos2 >= command.length()) break;
				else command.erase(0, pos2 + 1);
			}
		}
	}
}