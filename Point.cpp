#include "Point.h"

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}
void Point::setX(int _x) { x = _x; }
void Point::setY(int _y) { y = _y; }
void Point::setType(int _type) { type = _type;}
void Point::set(int _x, int _y, int _type)
{
	x = _x;
	y = _y;
	type = _type;
}
int Point::getX() { return x; }
int Point::getY() { return y; }
char Point::getType() { return type; }