#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Player
{
	string name;
	int countWin = 0;
	int countDraw = 0;
	int countLose = 0;

public:
	Player() = default;
	~Player() = default;
	void set(string _name, int _countWin, int _countDraw, int _countLose);
	void raiseWin();
	void raiseLose();
	void raiseDraw();
	int getWin();
	int getLose();
	int getDraw();
	void setName(string _name);
	string getName();
	float getWinRate();
};

