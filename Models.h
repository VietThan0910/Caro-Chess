#pragma once
#include <iostream>
#include "Match.h"
#include <map>
#include <unordered_map>
#include <fstream>
#include <string>

class Models
{
	unordered_map<string, Player> listPlayer;
	map<int, Match> listMatch;
	Match match;

public:
	void setMatch(Match& _match);
	Match& getMatch();
	unordered_map<string, Player> getListPlayer();
	map<int, Match>& getListMatch();
	pair<bool, Match*> getMatchByID(int _id);
	pair<bool, Player*> getPlayerByName(string _name);
	Player* insertPlayer(string _player);
	bool insertMatch(Match& _match);
	void readData();
};

