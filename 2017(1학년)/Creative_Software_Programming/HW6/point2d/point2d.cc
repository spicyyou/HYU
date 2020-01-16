#include "point2d.h"
#include<iostream>

using namespace std;
Point::Point()
{
}
	
Point::Point(Point const& p)
{
	//p.x_ = x_;
	//p.y_ = y_;
}
Point::Point(int c)
{
	x_ = c;
	y_ = c;
}
Point::Point(int x, int y)
{
	x_ = x;
	y_ = y;
}

Point Point::operator-()
{
	x_ = -x_;
	y_ = -y_;
	return Point();
}

void Point::print()
{
}

Point operator+(Point & lhs, Point & rhs)
{
	return(Point(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_));
}

Point operator-(Point & lhs, Point & rhs)
{
	//rhs.operator-();
	return Point(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}

Point operator*(Point & lhs, Point & rhs)
{
	return Point(lhs.x_* rhs.x_, lhs.y_ * rhs.y_);
}
