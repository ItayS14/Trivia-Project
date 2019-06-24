#include "RoomRequestHandler.h"
#include "Helper.h"
#include "json.hpp"

using json = nlohmann::json;

bool RoomRequestHandler::isRequestRelevant(const Request& request)
{
	if (!_is_admin && _room->_admin == _logged_user)
		_is_admin = true;
	return request._request_code == LEAVE_ROOM  || request._request_code == GET_ROOM_STATE || (request._request_code == START_GAME && _is_admin);
}

RequestResult RoomRequestHandler::handleRequest(const Request& request)
{
	RequestResult r;
	std::string r_msg = std::to_string(SUCCESS);
	try
	{
		json j = request._buffer.size() == 0 ? nullptr : json::parse(request._buffer);
		std::string data;
		switch (request._request_code)
		{
		case LEAVE_ROOM:
			leave();
			r._new_handler = _factory->createMenuRequestHandler(_logged_user);
			break;
		case START_GAME:
			_room->_state = IN_GAME;
			_room->_start_time = request._recival_time + 5; //Start game in 5 secs
			_game_manager->createGame(_room);
			r._new_handler = _factory->createGameRequestHandler(_logged_user, _game_manager->getGame(_room->_id), _room);
			break;
		case GET_ROOM_STATE:
			r._new_handler = this;
			data = Helper::handleGetRoomStateRequest(_room_manager, j.at("room_id"), _is_admin).dump();
			if (_room->_state == IN_GAME)
				r._new_handler = _factory->createGameRequestHandler(_logged_user, _game_manager->getGame(_room->_id), _room);
			break;
		}
		r_msg += Helper::getPaddedNumber(data.length(), SIZE_DIGIT_COUNT);
		r_msg += data;
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	catch (const std::exception& err)
	{
		std::string err_msg = err.what();
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err_msg.length(), SIZE_DIGIT_COUNT) + err_msg;
	}

	r._buffer = std::vector<std::uint8_t>(r_msg.begin(), r_msg.end());
	return r;
}


void RoomRequestHandler::leave()
{
	_room->removeUser(_logged_user);
	if (_room->getNumberOfLoggedUsers() == 0)
		_room_manager->deleteRoom(_room->_id);
}

void RoomRequestHandler::handleSocketError()
{
	leave();
	MenuRequestHandler* temp = _factory->createMenuRequestHandler(_logged_user);
	temp->handleSocketError();
	delete temp;
}
