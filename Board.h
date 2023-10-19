#pragma once
#include "Point.h"
#include <Windows.h>
#include <iostream>
using namespace std;
class Board
{
	int rows;
	int columns;
	Point origin;

public:
	
	void set(Point _origin, int _rows, int _columns);
	int getRows();
	int getColumns();
	Point getOrigin();
	void setCursorPosition(const int& posX, const int& posY);
	void plotBoard();
	void plotCaro(int x, int y, char type);
};

