#include "RequestHandlerFactory.h"

#define MIN_ISN_VAL 100
#define MAX_ISN_VAL 10000	

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
{
	std::srand(std::time(0)); // constructor will be only once in the program so this line is here.

	_login_manager = new LoginManager(database);
	_room_manager = new RoomManager(std::rand() % MAX_ISN_VAL + MIN_ISN_VAL);
	_game_manager = new GameManager(database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete _room_manager;
	delete _login_manager;
	delete _game_manager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string& username)
{
	return new MenuRequestHandler(username, _login_manager, _room_manager, this);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(_login_manager, this);
}

RoomRequestHandler* RequestHandlerFactory::createRoomRequestHandler(const std::string& username, Room* room, const bool is_admin)
{
	return new RoomRequestHandler(room, _room_manager, username, is_admin, _game_manager, this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const std::string& username, Game* game, Room* room)
{
	return new GameRequestHandler(username, game, _room_manager, _game_manager ,this);
}