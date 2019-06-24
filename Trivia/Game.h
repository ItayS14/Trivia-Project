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
	Question* getQuestion();
	double getScore(const std::string& player);
	size_t getNumberOfLoggedPlayers();
	unsigned int getId();
	void addScore(const std::string& player, const int index_of_answer);

private:
	unsigned int _id;
	unsigned int _request_counter; //counts how many players asked for the next question
	unsigned int _curr_question;
	std::vector<Question*> _questions;
	std::map<std::string, double> _players; //string for player name, double for his/her score
};
