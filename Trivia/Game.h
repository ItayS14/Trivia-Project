#pragma once
#include <string>
#include <vector>
#include <map>
#include <string>
#include "Question.h"
#include <mutex>

class Game
{
public:
	Game(std::vector<Question*> questions, std::map<std::string,double> players, int id) : _questions(questions), _players(players), _id(id) {}
	~Game();

	void removePlayer(const std::string& name);
	Question* getQuestionAt(const int index);
	
	double getScore(const std::string& player);
	
	std::map<std::string, double> getLeaderBoard();
	size_t getNumberOfLoggedPlayers();
	
	unsigned int getId();
	void addScore(const std::string& player, const int question, const int index_of_answer, time_t delta_time);

private:
	unsigned int _id;
	std::vector<Question*> _questions;
	std::map<std::string, double> _players; //string for player name, double for his/her score
	std::mutex _mtx;
};
