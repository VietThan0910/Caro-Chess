#include "Player.h"
void Player::set(string _name, int _countWin, int _countDraw, int _countLose)
{
	name = _name;
	countWin = _countWin;
	countDraw = _countDraw;
	countLose = _countLose;
}
void Player::raiseWin() { countWin++; }
void Player::raiseLose() { countLose++; }
void Player::raiseDraw() { countDraw++; }
int Player::getWin(){ return countWin; }
int Player::getLose() { return countLose; }
void Player::setName(string _name) { name = _name; }
string Player::getName() { return name; }
int Player::getDraw() { return countDraw; }
float Player::getWinRate()
{
	if (countWin != 0 )
	{
		return (float)(countWin / (countWin + countLose + countDraw)*100);
	}
	else
	{
	    return 0;
	}
}
