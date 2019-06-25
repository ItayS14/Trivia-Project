#include "Game.h"

Game::~Game()
{
	for (Question* q : _questions)
		delete q;
}

void Game::removePlayer(const std::string& name)
{
	std::lock_guard<std::mutex> lck(_mtx);
	_players.erase(name);
}


std::map<std::string, double> Game::getLeaderBoard()
{
	return _players;
}
Question* Game::getQuestionAt(const int index)
{
	if (index >= _questions.size())
		throw std::string("There are no more questions");
	return _questions[index];
}

double Game::getScore(const std::string& player) // no need for mutex here becuase addScore and getScore  for a user would never be at the same time 
{
	return _players[player];
}

size_t Game::getNumberOfLoggedPlayers()
{
	std::lock_guard<std::mutex> lck(_mtx);
	return _players.size();
}

unsigned int Game::getId()
{
	return _id;
}

void Game::addScore(const std::string & player, const int question, const int index_of_answer,time_t delta_time) // no need for mutex here becuase addScore and getScore for a user would never be at the same time (They are called in a row)
{
	if (question >= _questions.size())
		throw std::string("There are no more questions");
	if (_questions[question]->_correct_ans == index_of_answer)
		_players[player] += 5 * delta_time;
}
