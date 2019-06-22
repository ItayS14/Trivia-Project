#pragma once

#include "Requests.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomRequestHandler : public IRequestHandler
{
public:
	RoomRequestHandler(Room* room, RoomManager* room_manager, const std::string& logged_user, const bool is_admin, RequestHandlerFactory* factory) :
		_room(room), _room_manager(room_manager), _factory(factory), _logged_user(logged_user), _is_admin(is_admin) {}

	bool isRequestRelevant(const Request& request) override;
	RequestResult handleRequest(const Request& request) override;
	void handleSocketError() override;

private:
	void leave(); // (if user leaves and there is no more users the room would be closed)

	Room* _room;
	RoomManager* _room_manager;
	RequestHandlerFactory* _factory;
	std::string _logged_user;
	bool _is_admin;
};