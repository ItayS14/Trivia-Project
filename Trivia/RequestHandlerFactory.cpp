#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
{
	_login_manager = new LoginManager(database);
	_room_manager = new RoomManager();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete _room_manager;
	delete _login_manager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string& username)
{
	return new MenuRequestHandler(username, _login_manager, _room_manager);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(_login_manager, this);
}
