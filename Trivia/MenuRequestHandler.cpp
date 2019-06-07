#include "MenuRequestHandler.h"
#include "json.hpp"
#include "Helper.h"

using json = nlohmann::json;

bool MenuRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGOUT || request._request_code == JOIN_ROOM || request._request_code == CREATE_ROOM ||
		request._request_code == GET_PLAYERS_IN_ROOM || request._request_code == GET_ROOMS;
}

RequestResult MenuRequestHandler::handleRequest(const Request& request)
{
	json j = json::parse(request._buffer);
	RequestResult r;
	std::string r_msg;
	try
	{
		switch (request._request_code)
		{
		case LOGOUT:
			_login_manager->logout(_logged_user);
			r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
			break;
		case CREATE_ROOM:
			_room_manager->createRoom(j["room_name"], j["max_players"], j["time_per_question"], j["question_count"], j["type"]);
			r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
			break;
		case JOIN_ROOM:
			_room_manager->getRoom(j["room_id"]).addUser(_logged_user);	
			r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
			break;
		case GET_ROOMS:
			break;
		case GET_PLAYERS_IN_ROOM:
			json result_j;
			result_j["players"] = _room_manager->getRoom(j["room_id"]).getAllUsers();
			std::string j_as_string = result_j.dump();
			r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(j_as_string.length(), SIZE_DIGIT_COUNT) + j_as_string;
			break;
		}
		r._new_handler = this; 
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	return r;
}
