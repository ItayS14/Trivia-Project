#pragma once

#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <map>

class GameManager
{
public:
	GameManager(IDatabase* db) : _db(db) {}
	~GameManager();
	
	void createGame(Room* room);
	void deleteGame(unsigned int id);
	Game* getGame(unsigned int id);

private:
	IDatabase* _db;
	std::map<unsigned int, Game*> _games;
};