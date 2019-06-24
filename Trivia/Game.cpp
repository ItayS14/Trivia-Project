#include "Game.h"

Game::~Game()
{
	for (Question* q : _questions)
		delete q;
}

void Game::removePlayer(const std::string& name)
{
	_players.erase(name);
}

Question* Game::getQuestion()
{
	if (++_request_counter == _players.size())
	{
		_request_counter = 0;
		return _questions[_curr_question++];
	}
	return _questions[_curr_question];
}

double Game::getScore(const std::string& player)
{
	return _players[player];
}

size_t Game::getNumberOfLoggedPlayers()
{
	return _players.size();
}

unsigned int Game::getId()
{
	return _id;
}

void Game::addScore(const std::string & player, const int index_of_question)
{
	if (_questions[_curr_question]->_correct_ans == index_of_question)
		_players[player] += 5;
}
