#ifndef point2d
#define point2d

#include<vector>
using namespace std;
struct Point {
public:
	int x_, y_; // ��� ����
	Point();
	Point(Point const& p);
	explicit Point(int c);
	Point(int x, int y);
	Point operator-(); // ���� - ������
	void print();
	
};
Point operator+(Point& lhs, Point& rhs);
Point operator-(Point& lhs, Point& rhs);
Point operator*(Point& lhs, Point& rhs);

#endif
