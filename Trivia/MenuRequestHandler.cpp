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
	std::string r_msg = std::to_string(SUCCESS);
	std::string data = "";
	try
	{
		switch (request._request_code)
		{
		case LOGOUT:
		{
			_login_manager->logout(_logged_user);
			break;
		}
		case CREATE_ROOM:
		{
			_room_manager->createRoom(j["room_name"], j["max_players"], j["time_per_question"], j["question_count"], j["type"]);
			break;
		}
		case JOIN_ROOM:
		{
			_room_manager->getRoom(j["room_id"]).addUser(_logged_user);
			break;
		}
		case GET_ROOMS:
		{
			json result_j;
			for (Room& room : _room_manager->getRooms())
			{
				json inner_j;
				inner_j["room_id"] = room._id;
				inner_j["room_name"] = room._name;
				inner_j["max_players"] = room._max_players;
				inner_j["logged_players"] = room.getNumberOfLoggedUsers();
				inner_j["state"] = room.getState();
				inner_j["type"] = room._questions_type;
				result_j.push_back(inner_j);
			}
			data = result_j.dump();
			break;
		}
		case GET_PLAYERS_IN_ROOM:
		{
			json result_j(_room_manager->getRoom(j["room_id"]).getAllUsers());
			data = result_j.dump();
			break;
		}
		}
		r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(data.length(), SIZE_DIGIT_COUNT) + data;
		r._new_handler = this; 
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	r._buffer = std::vector<std::uint8_t>(r_msg.begin(), r_msg.end());
	return r;
}
