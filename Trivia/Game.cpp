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

Question* Game::getQuestionAt(int index)
{
	if (index < 0 || _questions.size() < -index)
		throw std::string("Index out of boundaries");
	return _questions[index];
}

double Game::getScore(const std::string& player)
{
	return _players[player];
}