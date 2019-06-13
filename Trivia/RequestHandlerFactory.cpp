#include "RequestHandlerFactory.h"

#define MIN_ISN_VAL 100
#define MAX_ISN_VAL 10000	

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
{
	std::srand(std::time(0)); // constructor will be only once in the program so this line is here.

	_login_manager = new LoginManager(database);
	_room_manager = new RoomManager(std::rand() % MAX_ISN_VAL + MIN_ISN_VAL);
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
