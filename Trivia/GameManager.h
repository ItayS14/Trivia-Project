#pragma once

#include "IDatabase.h"
#include "Game.h"
#include "Room.h"

class GameManager
{
public:
	Game* createGame(Room room);
	void deleteGame(Game* game);
private:
	IDatabase* _db;
	std::vector<Game*> _games;
};