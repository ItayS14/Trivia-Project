#include "RoomRequestHandler.h"
#include "Helper.h"
#include "json.hpp"

using json = nlohmann::json;

bool RoomRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LEAVE_ROOM || (request._request_code == START_GAME && _is_admin);
}

RequestResult RoomRequestHandler::handleRequest(const Request& request)
{
	RequestResult r;
	std::string r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
	try
	{
		json result_j;
		json j = request._buffer.size() == 0 ? nullptr : json::parse(request._buffer);
		std::string data;
		
		switch (request._request_code)
		{
		case LEAVE_ROOM:
			leaveRoom();
			r._new_handler = _factory->createMenuRequestHandler(_logged_user);
			break;
		case START_GAME:
			_room->_state = IN_GAME;
			r._new_handler = this; // change this later to be game handler
			break;
		}
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

void RoomRequestHandler::leaveRoom()
{
	_room->removeUser(_logged_user);
	if (_is_admin)
		_room_manager->deleteRoom(_room->_id);
}

void RoomRequestHandler::handleSocketError()
{
	leaveRoom();
	MenuRequestHandler* temp = _factory->createMenuRequestHandler(_logged_user);
	temp->handleSocketError();
	delete temp;
}