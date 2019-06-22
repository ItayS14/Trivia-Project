#pragma once
#include <string>
#include <vector>
#include <map>
#include <string>
#include "Question.h"

class Game
{
public:
	Game(std::vector<Question*> questions, std::map<std::string,double> players) : _questions(questions), _players(players) {}
	void removePlayer(const std::string& name);

private:
	std::vector<Question*> _questions;
	std::map<std::string, double> _players; //string for player name, double for his/her score
};
