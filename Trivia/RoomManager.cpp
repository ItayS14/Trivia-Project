#include "RoomManager.h"

void RoomManager::createRoom(const std::string& name, const unsigned int max_players, const unsigned int time_per_question, const bool is_active)
{
	_rooms[_isn] = Room(_isn, max_players, time_per_question, name, is_active);
	_isn++;
}

void RoomManager::deleteRoom(const unsigned int id)
{
	auto iterator = _rooms.find(id);
	if (iterator == _rooms.end())
		throw "Room not found";
	_rooms.erase(iterator);
}

bool RoomManager::getRoomState(const unsigned int id)
{
	if (_rooms.find(id) == _rooms.end())
		throw "Room not found";
	return _rooms[id].getState();
}
std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> r;
	for (auto& pair : _rooms)
		r.push_back(pair.second);
	return r;
}