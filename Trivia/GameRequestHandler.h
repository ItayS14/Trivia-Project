#pragma once

#include "Requests.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class GameRequestHandler : IRequestHandler
{
public:
	GameRequestHandler(Game* game, GameManager* game_manager, const std::string& logged_user, RequestHandlerFactory* factory) :
		_game(game), _game_manager(game_manager), _factory(factory), _logged_user(logged_user), {}

	bool isRequestRelevant(const Request& request) override;
	RequestResult handleRequest(const Request& request) override;
	void handleSocketError() override;

private:
	void leave(); // (if user leaves and there is no more users the game would be closed)

	Game* _game;
	GameManager* _game_manager;
	RequestHandlerFactory* _factory;
	std::string _logged_user;
};