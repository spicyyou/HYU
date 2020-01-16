#ifndef draw_shape2
#define draw_shape2
#include<iostream>
#include <vector>

using namespace std;
class Canvas {
public:
	Canvas(size_t row, size_t col);
	~Canvas();
	vector< vector<char> > draw;
	vector<char>::iterator it;
	//canvas ũ�⸦ w * h�� �����Ѵ�. �׷��� ������ �����Ѵ�.
	void Resize(size_t w, size_t h);
	//(x,y) ��ġ�� ���ڸ� �׸���. ���� ���� x,y�� �����Ѵ�.
	bool Draw(int x, int y, char brush);
	//�׷��� ������ ��� �����.('.'���� �ʱ�ȭ)
	void Clear();
	int row_;
	int col_;
	char brush_;
	int x_;
	int y_;
private:
	//�׷��� ����� ������ �� �ֵ��� �����͸���� ���� (resize ���ɿ� ����)
	friend ostream& operator<<(ostream& os, const Canvas& c);
};

class Shape {
public:
	virtual ~Shape();
	virtual void Draw(Canvas* canvas) const =0 ;
	string type_() { return type; }
	int x_() { return x; }
	int y_() { return y; }
	string type;
	int width_() { return width; }
	int height_() { return height; }
	char brush_() { return brush; }
	int x, y;
	int width, height;
	char brush;

protected:
	

};
class Rectangle : public Shape { void Draw(Canvas* canvas) const; };
class UpTriangle :public Shape { virtual void Draw(Canvas* canvas) const; };
class DownTriangle : public Shape { virtual void Draw(Canvas* canvas) const; };
class Diamond : public Shape { virtual void Draw(Canvas* canvas) const; };

istream& operator >> (istream& is, Rectangle& r);
istream& operator >> (istream& is, UpTriangle& t);
istream& operator >> (istream& is, DownTriangle& d);
istream& operator >> (istream& is, Diamond& dm);

#endif