#pragma once
#include <string>
#include <vector>
#include <map>
#include <string>
#include "Question.h"

class Game
{
public:
	Game(std::vector<Question*> questions, std::map<std::string,double> players, int id) : _questions(questions), _players(players), _id(id) {}
	~Game();

	void removePlayer(const std::string& name);
	Question* getQuestionAt(int index); // throws exception if index is out of bounds

private:
	unsigned int _id;
	std::vector<Question*> _questions;
	std::map<std::string, double> _players; //string for player name, double for his/her score
};
