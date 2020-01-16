#include "minesweeper.h"
#include <string>
#include<iostream>
#include<stdlib.h>
using namespace std;

int main() {
	Minesweeper *_minesweeper = new Minesweeper;
	while (true) {
		string inputs;
		getline(cin, inputs);
		size_t pos = inputs.find(' ');
		string token = inputs.substr(0, pos);
		vector<string> map_main;
		if (token == ":set") {
			inputs.erase(0, pos+1);
			size_t pos1 = inputs.find(' ');
			string width_num = inputs.substr(0,pos1);
			inputs.erase(0, pos1+1);
			string height_num = inputs;
			size_t _width = atoi(width_num.c_str());//얘네를 함수에서 인자로 받을거임
			size_t  _height = atoi(height_num.c_str());
			string arr;
			//vector<string> map_main;
			for (int i = 0; i < _height; i++) {
				{
					getline(cin, arr);
					map_main.push_back(arr);
				}
			}
			_minesweeper->setMap(_width, _height, map_main);
			map_main.clear();
			//set 함수 play하기
		}

		else if (token == ":toggle") {
			//toggle play 하기
			int _x = inputs[8] - '0';//toggle
			int _y = inputs[10] - '0';
			_minesweeper->toggleMine(_x, _y);
		}
		else if (token == ":play") {
			//play 하기
			_minesweeper->setPlay();
		}
		else if (token == ":touch") {
			//touch하기
			int _x2 = inputs[7] - '0';//touch
			int _y2 = inputs[9] - '0';
			//_minesweeper->touchMap(_x2, _y2);
			if(_minesweeper->touchMap(_x2, _y2)==true){
				cout << "DEAD(" << _minesweeper->touchCount() << ")" << endl;
			}
		}
		else if (token == ":quit") {
			break;
		}
		inputs = "";
		//map_main.clear();
	}
}