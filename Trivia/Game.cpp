#include "Game.h"

void Game::removePlayer(const std::string& name)
{
	_players.erase(name);
}