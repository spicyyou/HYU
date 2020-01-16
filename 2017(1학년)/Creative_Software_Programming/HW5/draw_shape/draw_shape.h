#ifndef draw_shape
#define draw_shape

#include<iostream>
#include<string>
#include<vector>

using namespace std;
enum { RECTANGLE, TRIANGLE_UP, TRIANGLE_DOWN };
enum { ERROR_OUT_OF_CANVAS = -1, ERROR_INVALID_INPUT = -2 };
struct Shape{ 
	int type; 
	int x, y; 
	int width, height;
	char brush;// The character to draw the shape
};
class Canvas {
public:
	char**draw;
	Canvas(size_t row, size_t col);
	~Canvas();
	int AddShape(const Shape &s);		// Return the index of the shape.
	void DeleteShape(int index);
	void Draw(ostream& os);
	void Dump(ostream& os);
private:
	int index;
	size_t row_, col_;
	vector<Shape> shapes_;
};
#endif