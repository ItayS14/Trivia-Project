#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomRequestHandler;

// every handler the factory makes is allocated on the heap therefore needs to be deleted later
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler(); 
	MenuRequestHandler* createMenuRequestHandler(const std::string& username);
	RoomRequestHandler* createRoomRequestHandler(const std::string& username, Room* room, const bool is_admin);

private:
	RoomManager* _room_manager;
	LoginManager* _login_manager;
};