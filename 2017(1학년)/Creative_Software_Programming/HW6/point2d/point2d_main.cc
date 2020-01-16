#include "point2d.h"
#include <iostream>
#include <string>
#include<vector>
#include<map>
#include<stdlib.h>
using namespace std;


int main() {
	pair<int, int> p_point;
	map<string, pair<int, int>> m_point;
	map<string, pair<int, int>> ::iterator it_left;
	map<string, pair<int, int>> ::iterator it_right;
	int isOkay = 0;
	int minus_left = 0;
	int minus_right = 0;
	while (1) {
		string command;
		cin >> command;
		if (command == "set") {
			string alpha; int a, b;
			cin >> alpha >> a >> b;
			p_point.first = a;
			p_point.second = b;
			m_point.insert(make_pair(alpha, p_point));
		}
		else if (command == "eval") {			
			string left_input, right_input; char oper;
			Point left;
			Point right;
			cin >> left_input >> oper >> right_input;
			for (int i = 0; i < left_input.length(); i++) {
				if (left_input[i] == '-') { minus_left = 1; }
			}
			for (int i = 0; i < right_input.length(); i++) {
				if (right_input[i] == '-') { minus_right = 1; }
			}
			if (atoi(left_input.c_str())!=0) { left.x_=atoi(left_input.c_str()); left.y_ = atoi(left_input.c_str());
			}
			else {
				if (minus_left != 1) {
					if ((m_point.find(left_input) == m_point.end())) { cout << "input error" << endl; isOkay = 1; }
				}
				else
				{
					string left_erase = left_input.erase(0, 1);
					if ((m_point.find(left_erase)) == m_point.end()) { cout << "input error" << endl; isOkay = 1; }
				}
				if (isOkay != 1) {
					it_left = m_point.begin();
					it_left == m_point.find(left_input);
					if (minus_left == 1) {
						left.x_ = (it_left->second.first)*-1;
						left.y_ = (it_left->second.second)*-1;
					}else {
						left.x_ = it_left->second.first;
						left.y_ = it_left->second.second;
					}
				}
			}
			if (atoi(right_input.c_str()) != 0) { right.x_ = atoi(right_input.c_str()); right.y_ = atoi(right_input.c_str()); }
			else {
				if (minus_right != 1) {
					if (m_point.find(right_input) == m_point.end()) { cout << "input error" << endl; isOkay = 1; }
				}
				else {
					string right_erase = right_input.erase(0,1);
										if ((m_point.find(right_erase)) == m_point.end()) { cout << "input error" << endl; isOkay = 1; }
				}
				if(isOkay!=1)
				{
					it_right = m_point.begin();
					it_right = m_point.find(right_input);
					if (minus_right == 1) {
						right.x_ = (it_right->second.first)*-1;
						right.y_ = (it_right->second.second)*-1;
					}
					else {
						right.x_ = it_right->second.first;
						right.y_ = it_right->second.second;
					}
				}
			} if (oper == '+'&&isOkay!=1) {
				cout<<"("<<(left + right).x_<<" ,"<<(left + right).y_<<")"<<endl;
			} else if (oper == '-'&&isOkay != 1) {
				cout << "(" << (left - right).x_ << " ," << (left - right).y_ << ")" << endl;
			} else if (oper == '*'&&isOkay != 1) {
				cout << "(" << (left * right).x_ << " ," << (left * right).y_ << ")" << endl;
			}
		}
		else if (command == "quit") { break; }
		minus_left = 0;
		minus_right = 0;
		isOkay = 0;
	}
}