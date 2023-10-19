#pragma once
#include "Point.h"
#include "Board.h"
#include <Windows.h>
#include "Match.h"
#include <iostream>
using namespace std;

#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15
#define defaultColor		7 

class Views
{
public:

	Board board;
	
	void setCursorPosition(const int& posX, const int& posY);
	void setBoad(Board _board);
	void setColor(int color);
	void dispBorder(Point origin, int width, int height);
	void dispSpaceSquare(Point origin, int width, int height);
	void dispMenu();
	void dispGame(Match match, Point origin, int width, int height);
	void dispDraw(Match match);
	void dispWin(Match match, char type, Point para1, int para2, int para3);
	void dispMatch(Match match);
	void setConsoleWindow(int w, int h);
};

