#include "MenuRequestHandler.h"
#include "json.hpp"

using json = nlohmann::json;

bool MenuRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGOUT || request._request_code == JOIN_ROOM || request._request_code == CREATE_ROOM;
}

RequestResult MenuRequestHandler::handleRequest(const Request& request)
{
	json j;
	switch (request._request_code)
	{
	case LOGOUT:
		_login_manager->logout(_logged_user);
		break;
	case CREATE_ROOM:
		_room_manager->createRoom(j["room_name"], j["max_players"], j["time_per_question"], j["question_count"]);	
		break;
	case JOIN_ROOM:
		_room_manager->getRoom(j["room_id"]).addUser(_logged_user);
		break;
	}

}
