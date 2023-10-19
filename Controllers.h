#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "Models.h"
#include "Views.h"
#include <string>

class Controllers
{
	Models models;
	Views views;

public:
	Player* checkPlayer(string name);
	void creatMatch(Board _board, Player& _player1, Player& _player2, int _firstTurn);
	void playGame();
	pair<char, pair<int, int>> checkWin(Match match, int _row, int _col);
	void replay(int id);
	void replay(Match match);
	pair<int, pair<int, int>> catchEvent(int& loop);
	void undo();
	void redo();
	bool checkAvail(Board board, int row, int col);
	void dispListPlayer();
	void dispListMatch();
	Player* insertPlayer(string _player);
	void setBoardinViews(Board board);
	void setConsoleWindow(int width, int height);
	void loopGame();
};