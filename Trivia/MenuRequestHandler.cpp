#include "MenuRequestHandler.h"
#include "json.hpp"
#include "Helper.h"

using json = nlohmann::json;

bool MenuRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGOUT || request._request_code == JOIN_ROOM || request._request_code == CREATE_ROOM;
}

RequestResult MenuRequestHandler::handleRequest(const Request& request)
{
	json j;	
	RequestResult r;
	std::string r_msg;
	try
	{
		switch (request._request_code)
		{
		case LOGOUT:
			_login_manager->logout(_logged_user);
			break;
		case CREATE_ROOM:
			_room_manager->createRoom(j["room_name"], j["max_players"], j["time_per_question"], j["question_count"], j["type"]);
			break;
		case JOIN_ROOM:
			_room_manager->getRoom(j["room_id"]).addUser(_logged_user);
			break;
		}
		r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
		r._new_handler = this; 
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	return r;
}
