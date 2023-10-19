#pragma once
class Point
{
	int x;
	int y;
	char type = 0;
public:
	Point() = default;
	Point(int _x, int _y);
	~Point() = default;
	void setX(int _x);
	void setY(int _y);
	void setType(int _type);
	void set(int _x, int _y, int _type);
	int getX();
	int getY();
	char getType();

};

