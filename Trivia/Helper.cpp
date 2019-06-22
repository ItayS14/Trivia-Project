#include "Helper.h"
#include <sstream>
#include <iomanip>

std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();
}

json Helper::handleGetRoomStateRequest(RoomManager* room_manager, const int room_id, const bool is_admin)
{
	json result_j;
	Room* room = room_manager->getRoom(room_id);
	result_j["room_id"] = room->_id;
	result_j["room_name"] = room->_name;
	result_j["max_players"] = room->_max_players;
	result_j["players"] = room->getAllUsers();
	result_j["is_admin"] = is_admin;
	result_j["state"] = room->_state;
	result_j["type"] = room->_questions_type;
	return result_j;
}