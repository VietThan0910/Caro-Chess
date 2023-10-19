#include "Match.h"

Match::Match(Board board,Player _player1, Player _player2, char _turn)
{
	player1 = _player1;
	player2 = _player2;
	vector<vector<char>> v(board.getRows(), vector<char>(board.getColumns(), '\0'));
}
Board Match::getBoard()
{
	return board;
}

vector<vector<char>>& Match::getMapCaro()
{
	return mapCaro;
}

void Match::setTurn(char _turn)
{
	turn = _turn;
}
char Match::getTurn()
{
	return turn;
}
void Match::changeTurn()
{
	turn = -turn;
}
void Match::setCompleted()
{
	status = 1;
}
bool Match::isCompleted()
{
	return status;
}

int Match::getID() { return id; }
void Match::set(Board _board, Player& _player1, Player& _player2, char _turn)
{
	id = ++id;
	player1 = _player1;
	player2 = _player2;
	board = _board;
	vector<vector<char>> tmp(board.getRows(), vector<char>(board.getColumns(), '\0'));
	mapCaro = tmp;
	vctMove.clear();
	vctMoveExtra.clear();
	turn = _turn;
	countX = 0;
	countO = 0;
	status = 0;
}
Player& Match::getPlayer1() { return player1; }
Player& Match::getPlayer2() { return player2; }
vector<Point>& Match::getVctMove() { return vctMove; }
vector<Point>& Match::getVctMoveExtra() { return vctMoveExtra; }
int Match::getCountX() { return countX; }
int Match::getCountO() { return countO; }
void Match::setCountX(int _delta) { countX += _delta; }
void Match::setCountY(int _delta) { countO += _delta; }

