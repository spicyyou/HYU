#ifndef point2d
#define point2d

#include<vector>
using namespace std;
struct Point {
public:
	int x_, y_; // 멤버 변수
	Point();
	Point(Point const& p);
	explicit Point(int c);
	Point(int x, int y);
	Point operator-(); // 전위 - 연산자
	void print();
	
};
Point operator+(Point& lhs, Point& rhs);
Point operator-(Point& lhs, Point& rhs);
Point operator*(Point& lhs, Point& rhs);

#endif
