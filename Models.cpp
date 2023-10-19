#include "Models.h"
#include <algorithm>

bool comparePlayer(pair<string, Player>& obj1, pair<string, Player>& obj2)
{
	return obj1.second.getWinRate() > obj2.second.getWinRate();
}

unordered_map<string, Player> sortListPlayer(unordered_map<string, Player> map)
{
	vector<pair<string, Player>> vct;
	for (auto& it : map) {
		vct.push_back(it);
	}
	sort(vct.begin(), vct.end(), comparePlayer);
	map.clear();
	for (auto& it : vct) {
		map.insert(it);
	}
	return map;
}

void Models::setMatch(Match& _match)
{
	match = _match;
}
Match& Models::getMatch()
{
	return match;
}
unordered_map<string, Player> Models::getListPlayer()
{
	return sortListPlayer(listPlayer);
}
map<int, Match>& Models::getListMatch()
{
	return listMatch;
}

pair<bool, Match*> Models::getMatchByID(int _id)
{
	auto it = listMatch.find(_id);
	if (it != listMatch.end()) return { 1, &it->second };
	else return { 0, nullptr };
}
pair<bool, Player*> Models::getPlayerByName(string _name)
{
	auto it = listPlayer.find(_name);
	if (it != listPlayer.end()) return { 1, &it->second };
	else return { 0, nullptr };
}

Player* Models::insertPlayer(string _player)
{
	Player player;
	player.setName(_player);
	return &(listPlayer.insert({ _player, player }).first->second);
}
bool Models::insertMatch(Match& _match)
{
	return listMatch.insert({ _match.getID(), _match }).second;
}


