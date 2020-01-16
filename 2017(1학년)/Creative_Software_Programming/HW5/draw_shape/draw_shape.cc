ei#include "draw_shape.h"
#include<iostream>
#include<vector>
using namespace std;
Canvas::Canvas(size_t row, size_t col)
{
	row_ = row;
	col_ = col;
	draw = new char*[row_];
	for (int i = 0; i < row_; i++) {
		draw[i] = new char[col_];
	}
}

Canvas::~Canvas()
{
}

int Canvas::AddShape(const Shape & s)
{
	if (1) {
		if (s.type == RECTANGLE) {
			if (s.width / 2 + s.x > col_ || s.x - s.width / 2 < 0 || s.height / 2 + s.y > row_ || s.y-(s.height/2)<0)
			{
				cout << "error out of canvas" << endl;
				return ERROR_OUT_OF_CANVAS;
			}
			else if (s.width % 2 != 1 || s.height % 2 != 1) {
				cout << "error invalid input" << endl;
				return ERROR_INVALID_INPUT;
			}
			else {
				shapes_.push_back(s);
				return shapes_.size() - 1;
			}
		}
		else if (s.x < 0 || s.y < 0 || s.x >= col_ || s.y >= row_) {
			cout << "error out of canvas" << endl;
			return ERROR_OUT_OF_CANVAS;
		}
		else if (s.type == TRIANGLE_UP) {
			if (s.y + s.height > row_) {
				cout << "error out of canvas" << endl;
				return ERROR_OUT_OF_CANVAS;
			}
			else if (s.x - s.height + 1 < 0 || s.x + s.height > col_) {
				cout << "error out of canvas" << endl;
				return ERROR_OUT_OF_CANVAS;
			}
			else {
				shapes_.push_back(s);
				return shapes_.size() - 1;
			}
		}
		else if(s.type==TRIANGLE_DOWN)
		{
			if (s.y - s.height > row_) {
				cout << "error out of canvas" << endl;
				return ERROR_OUT_OF_CANVAS;
			}
			else if (s.x - s.height + 1 < 0 || s.x + s.height > col_) {
				cout << "error out of canvas" << endl;
				return ERROR_OUT_OF_CANVAS;
			}
			else {
				shapes_.push_back(s);
				return shapes_.size() - 1;
			}
		}
	}
}

void Canvas::DeleteShape(int index)
{
	if (shapes_.size() <= index)
		return;
	shapes_.erase(shapes_.begin()+index);
}

void Canvas::Draw(ostream & os)
{
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			draw[i][j] = '.';
		}
	}
	int j_minus = 0;
	for (int i = 0; i < shapes_.size(); i++) {
		if (shapes_[i].type == RECTANGLE) {
			for (int j = shapes_[i].y - (shapes_[i].height / 2); j <= shapes_[i].y + (shapes_[i].height / 2); j++) {
				for (int k = shapes_[i].x - (shapes_[i].width / 2); k <= shapes_[i].x + (shapes_[i].width / 2); k++) {
					draw[j][k] = shapes_[i].brush;
				}
			}
		}
		else if (shapes_[i].type == TRIANGLE_UP) {
			for (int j = shapes_[i].y, j_minus = 0; j < shapes_[i].y + shapes_[i].height; j++, j_minus++) {
				for (int k = shapes_[i].x - j_minus; k <= shapes_[i].x + j_minus; k++) {
					draw[j][k] = shapes_[i].brush;
				}
			}
		}
		else if (shapes_[i].type == TRIANGLE_DOWN) {
			for (int j = shapes_[i].y, j_minus = 0; j > shapes_[i].y - shapes_[i].height; j--, j_minus++) {
				for (int k = shapes_[i].x - j_minus; k <= shapes_[i].x + j_minus; k++) {
					draw[j][k] = shapes_[i].brush;
				}
			}
		}
	}

	os << ' ';
	for (int i = 0; i < col_; i++) {
		if (i >= 10) {
			os << i-10;
		}
		else
			os << i;
	}
	os << endl;
	for (int i = 0; i < row_; i++) {
		if (i >= 10) {
			os << i - 10;
		}
		else
			os << i;
		for (int j = 0; j < col_; j++) {
			os << draw[i][j];
		}
		os << endl;
	}
	return;
}

void Canvas::Dump(ostream & os)
{
	for (int i = 0; i < shapes_.size(); i++) {
		if (shapes_[i].type == RECTANGLE)
		{
			os << i << " rect " << shapes_[i].x << ' ' << shapes_[i].y << ' ' << shapes_[i].width << ' ' << shapes_[i].height << ' ' << shapes_[i].brush << endl;
		}
		else if (shapes_[i].type == TRIANGLE_UP) {
			os << i << " tri_up " << shapes_[i].x << ' ' << shapes_[i].y << ' ' << shapes_[i].height << ' ' << shapes_[i].brush << endl;
		}
		else if (shapes_[i].type == TRIANGLE_DOWN) {
			os << i << " tri_down " << shapes_[i].x << ' ' << shapes_[i].y << ' ' << shapes_[i].height << ' ' << shapes_[i].brush << endl;
		}
	}
	return;
}