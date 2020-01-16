#include "draw_shape2.h"

Shape::~Shape()
{
}

void Rectangle::Draw(Canvas * canvas) const
{
	int isOkay = 0;
	int width_temp;
	int height_temp;
	if (x < 0 || y < 0 )
	{ isOkay = 1; }
	if (isOkay == 0) {
		for (int j = y; j < y + height; j++) {
			for (int k = x; k < x + width; k++) {
				if (k < canvas->col_ && j < canvas->row_) {
					canvas->draw[j][k] = brush;
				}
			}
		}
	}
}

void UpTriangle::Draw(Canvas * canvas) const
{
	
	int isOkay = 0; 
	if (x < 0 || y < 0 )
	if(isOkay==0){
		for (int j = y, j_minus = 0; j < y + height; j++, j_minus++) {
			for (int k = x - j_minus; k <= x + j_minus; k++) {
				if (j < canvas->row_&& k>=0&&k<canvas->col_) {
					canvas->draw[j][k] = brush;
				}
			}
		}
	}
}

void DownTriangle::Draw(Canvas * canvas) const
{
	int isOkay = 0;
	
	if (x < 0 || y < 0 )
	{ isOkay = 1; }
	if (isOkay == 0) {
		for (int j = y, j_minus = 0; j > y - height; j--, j_minus++) {
			for (int k = x - j_minus; k <= x + j_minus; k++) {
				if (j < canvas->row_&& k >= 0 && k < canvas->col_&&j >= 0) {
					canvas->draw[j][k] = brush;
				}
			}
		}
	}
}

void Diamond::Draw(Canvas * canvas) const
{
	int isOkay = 0;
	int y_temp = y + (height * 2);
	//tri_up
	if (x < 0 || y < 0 || y_temp<0 ) 
	{
		isOkay = 1;
	}
	if (isOkay == 0) {
		for (int j = y, j_minus = 0; j < y + height+1; j++, j_minus++) {
			for (int k = x - j_minus; k <= x + j_minus; k++) {
				if (j < canvas->row_&& k >= 0 && k<canvas->col_) {
					canvas->draw[j][k] = brush;
				}
			}
		}
		//+높이*2
		for (int j = y_temp, j_minus = 0; j > y_temp - height; j--, j_minus++) {
			for (int k = x - j_minus; k <= x + j_minus; k++) {
				if (j < canvas->row_ && k>= 0 && k< canvas->col_&&j>=0) {
					canvas->draw[j][k] = brush;
				}
			}
		}
	}
}

Canvas::Canvas(size_t row, size_t col)
{
	row_ = row;
	col_ = col;
	draw.resize(row_);
	for (int i = 0; i < row_; i++) {
		draw[i].resize(col_);
	}
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			draw[i][j] = '.';
		}
	}
}

Canvas::~Canvas()
{
}

void Canvas::Resize(size_t w, size_t h)
{
	//draw.clear();
	row_ = h;
	col_ = w;
	draw.resize(row_);
	for (int i = 0; i < row_; i++) {
		draw[i].resize(col_);
	}
}

bool Canvas::Draw(int x, int y, char brush)
{
	x_ = x;
	y_ = y;
	brush_ = brush;
	return true;
}

void Canvas::Clear()
{
	draw.clear();
	Resize(col_, row_);
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			draw[i][j] = '.';
		}
	}
}

ostream & operator<<(ostream & os, const Canvas & c)
{
	os << ' ';
	for (int i = 0; i < c.col_; i++) {
		if (i >= 10) {
			os << i - 10;
		}
		else
			os << i;
	}
	os << endl;
	for (int i = 0; i < c.row_; i++) {
		if (i >= 10) {
			os << i - 10;
		}
		else
			os << i;
		for (int j = 0; j < c.col_; j++) {
			os << c.draw[i][j];
		}
		os << endl;
	}
	return os;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

istream & operator >> (istream & is, Rectangle & r)
{
	is >> r.x >> r.y >> r.width >> r.height>>r.brush;
	return is;
		// TODO: 여기에 반환 구문을 삽입합니다.
}

istream & operator >> (istream & is, UpTriangle & t)
{
	is >> t.x >> t.y>> t.height>>t.brush;

	return is;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

istream & operator >> (istream & is, DownTriangle & d)
{
	is >> d.x>> d.y >> d.height>>d.brush;
	return is;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

istream & operator >> (istream & is, Diamond & dm)
{
	is >> dm.x >> dm.y >> dm.height>>dm.brush;
	return is;
	// TODO: 여기에 반환 구문을 삽입합니다.
}