#include "draw_shape.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
using namespace std;

int main() {
	int num = 0;
	int row, col;
	cin >> row >> col;
	Canvas canvas(col,row);
	canvas.Draw(cout);
	while (true) {
		string inputs;
		getline(cin, inputs);
		size_t pos = inputs.find(' ');
		string token = inputs.substr(0, pos);
		if (token == "add") {
			inputs.erase(0, pos + 1);
			size_t pos_command = inputs.find(' ');
			string token_command = inputs.substr(0, pos_command);
			if (token_command == "rect") {
				inputs.erase(0, pos_command + 1);
				size_t pos_x = inputs.find(' ');
				Shape rect;
				rect.x = atoi((inputs.substr(0, pos_x)).c_str());
				inputs.erase(0, pos_x + 1);
				size_t pos_y = inputs.find(' ');
				rect.y = atoi((inputs.substr(0, pos_y)).c_str());
				inputs.erase(0, pos_y + 1);
				size_t pos_width = inputs.find(' ');
				rect.width= atoi((inputs.substr(0, pos_width)).c_str());
				inputs.erase(0, pos_width + 1);
				size_t pos_height = inputs.find(' ');
				rect.height = atoi((inputs.substr(0, pos_height)).c_str());
				inputs.erase(0, pos_height + 1);
				rect.brush = *inputs.c_str();
				rect.type = RECTANGLE;
				canvas.AddShape(rect);
				//rectangular 입력
			}
			else if (token_command == "tri_up") {
				inputs.erase(0, pos_command + 1);
				size_t pos_x = inputs.find(' ');
				Shape tri_up;
				tri_up.x = atoi((inputs.substr(0, pos_x)).c_str());
				inputs.erase(0, pos_x + 1);

				size_t pos_y = inputs.find(' ');
				tri_up.y = atoi((inputs.substr(0, pos_y)).c_str());
				inputs.erase(0, pos_y + 1);

				size_t pos_height = inputs.find(' ');
				tri_up.height = atoi((inputs.substr(0, pos_height)).c_str());
				inputs.erase(0, pos_height + 1);

				tri_up.brush = *inputs.c_str();
				tri_up.type = TRIANGLE_UP;
				canvas.AddShape(tri_up);
				//넘는지 안넘는지 조건문 추가>>add 함서에 넣었움

			}
			else if (token_command == "tri_down") {
				inputs.erase(0, pos_command + 1);
				size_t pos_x = inputs.find(' ');
				Shape tri_down;
				tri_down.x = atoi((inputs.substr(0, pos_x)).c_str());
				inputs.erase(0, pos_x + 1);

				size_t pos_y = inputs.find(' ');
				tri_down.y = atoi((inputs.substr(0, pos_y)).c_str());
				inputs.erase(0, pos_y + 1);

				size_t pos_height = inputs.find(' ');
				tri_down.height = atoi((inputs.substr(0, pos_height)).c_str());
				inputs.erase(0, pos_height + 1);

				tri_down.brush = *inputs.c_str();
				tri_down.type = TRIANGLE_DOWN;
				canvas.AddShape(tri_down);
			}
		}
		else if (token == "draw") {
			canvas.Draw(cout);
		}
		else if (token == "dump") {
			canvas.Dump(cout);
		}
		else if (token == "delete") {
			inputs.erase(0, pos + 1);
			int num = atoi(inputs.c_str());
			canvas.DeleteShape(num);
		}
		else if (token == "quit") {
			break;
		}
		num = 0;
	}
}