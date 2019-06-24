#pragma once

#include "Requests.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(const std::string& logged_user, Game* game,  Room* room, GameManager* game_manager, RequestHandlerFactory* factory) :
		_game(game), _game_manager(game_manager), _factory(factory), _logged_user(logged_user), _room(room), _question(0) {}

	bool isRequestRelevant(const Request& request) override;
	RequestResult handleRequest(const Request& request) override;
	void handleSocketError() override;

private:
	void leave(); // (if user leaves and there is no more users the game would be closed)

	Game* _game;
	Room* _room; // room of the game (here to handle socket erros)
	GameManager* _game_manager;
	RequestHandlerFactory* _factory;
	std::string _logged_user;
	int _question; // counter for current question
};