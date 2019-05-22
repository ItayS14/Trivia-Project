#pragma once

#include <string>
#include "RoomManager.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "Requests.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const std::string& logged_user, LoginManager* login_manager, RoomManager* room_manager)
		: _logged_user(logged_user), _login_manager(login_manager), _room_manager(room_manager) {}

	bool isRequestRelevant(const Request& request);
	RequestResult handleRequest(const Request& request);

private:	
	std::string _logged_user;
	//high score - manager
	LoginManager* _login_manager; // for signing out
	RoomManager* _room_manager;
	RequestHandlerFactory* _factory;
};