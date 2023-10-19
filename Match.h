#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include "Player.h"
#include "Board.h"
using namespace std;
class Match
{
	int id = 0;
	Player player1;
	Player player2;
	Board board;
	vector<vector<char>> mapCaro;
	vector<Point> vctMove;
	vector<Point> vctMoveExtra;
	int countX;
	int countO;
	char turn;
	bool status = 1;
public:

	Match() = default;
	Match(Board board, Player _player1, Player _player2, char _turn);
	~Match() = default;
	int getID();
	void set(Board board, Player& _player1, Player& _player2, char _turn);
	Board getBoard();
	Player& getPlayer1();
	Player& getPlayer2();
	vector<Point>& getVctMove();
	vector<Point>& getVctMoveExtra();
	vector<vector<char>>& getMapCaro();
	int getCountX();
	int getCountO();
	void setCountX(int _delta);
	void setCountY(int _delta);
	void setTurn(char _turn);
	char getTurn();
	void changeTurn();
	void setCompleted();
	bool isCompleted();

};
