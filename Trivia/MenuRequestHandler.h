#pragma once

#include <string>
#include "RoomManager.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "Requests.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const std::string& logged_user, LoginManager* login_manager, RoomManager* room_manager, RequestHandlerFactory* factory)
		: _logged_user(logged_user), _login_manager(login_manager), _room_manager(room_manager), _factory(factory) {}

	bool isRequestRelevant(const Request& request) override;
	RequestResult handleRequest(const Request& request) override;
	void handleSocketError() override;
private:	
	std::string _logged_user;
	//high score - manager
	LoginManager* _login_manager; // for signing out
	RoomManager* _room_manager;
	RequestHandlerFactory* _factory;
};