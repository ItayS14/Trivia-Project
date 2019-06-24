#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomRequestHandler.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomRequestHandler;
class GameRequestHandler;

// every handler the factory makes is allocated on the heap therefore needs to be deleted later
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler(); 
	MenuRequestHandler* createMenuRequestHandler(const std::string& username);
	RoomRequestHandler* createRoomRequestHandler(const std::string& username, Room* room, const bool is_admin);
	GameRequestHandler* createGameRequestHandler(const std::string& username, Game* game, Room* room);

private:
	RoomManager* _room_manager;
	LoginManager* _login_manager;
	GameManager* _game_manager;
};