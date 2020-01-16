#include "draw_shape2.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main() {
	vector<Shape*> shapes;
	size_t row, col;
	cin >> row >> col;
	Canvas canvas(row, col);
	cout << canvas;
	while (true) {
		string tok;
		cin >> tok;
		if (tok == "add") {
			string type;
			cin >> type;
			if (type == "rect") {
				Rectangle *shape = new Rectangle();
				cin >> *shape;
				shape->type = "rect";
				shapes.push_back(shape);
			}
			else if (type == "tri_up") {
				UpTriangle * shape = new UpTriangle();
				cin >> *shape;
				shape->type = "tri_up";
				shapes.push_back(shape);
			}
			else if (type == "tri_down") {
				DownTriangle * shape = new DownTriangle();
				shape->type = "tri_down";
				cin >> *shape;
				shapes.push_back(shape);
			}
			else if (type == "diamond") {
				Diamond  *diamond = new Diamond();
				cin >> *diamond;
				diamond->type = "diamond";
				shapes.push_back(diamond);
			}
			else continue;
		}
		else if (tok == "draw") {
			canvas.Clear();
			for (int i = 0; i < shapes.size(); ++i) {
				shapes[i]->Draw(&canvas);
			}
			cout << canvas;
		}
		else if (tok == "delete") {
			int index;
			cin >> index;
			if (index < shapes.size()) { shapes.erase(shapes.begin() + index); }
		}
		else if (tok == "dump") {
			for (int i = 0; i < shapes.size(); ++i) {
				if (shapes[i]->type == "rect")
				{
					cout << i << " rect " << shapes[i]->x << ' ' << shapes[i]->y_() << ' ' << shapes[i]->width_() <<' '<< shapes[i]->height_()<< ' ' << shapes[i]->brush_() << endl;//너비,높이 중 먼저인거
				}
				else {
					cout << i << ' ' << shapes[i]->type << ' ' << shapes[i]->x_() << ' ' << shapes[i]->y_() << ' ' << shapes[i]->height_() << ' ' << shapes[i]->brush_() << endl;
				}
			}
		}
		else if (tok == "resize") {
			int row, dol;
			cin >> row >> col;
			canvas.Resize(row, col);
		}
		else {
			break;
		}
	}
	for (int i = 0; i < shapes.size(); ++i) {
		delete shapes[i];
	}
	shapes.clear();
	return 0;
}