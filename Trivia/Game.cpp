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

Question* Game::getQuestionAt(const int index)
{
	if (index > _questions.size())
		throw std::string("There are no more questions");
	return _questions[index];
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

void Game::addScore(const std::string & player, const int question, const int index_of_answer)
{
	if (_questions[question]->_correct_ans == index_of_answer)
		_players[player] += 5;
}
