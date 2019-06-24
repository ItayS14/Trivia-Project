#include "RoomManager.h"

RoomManager::~RoomManager()
{
	for (auto& pair : _rooms)
		delete pair.second;
}
int RoomManager::createRoom(const std::string& name, const unsigned int max_players, const unsigned int time_per_question, const unsigned int question_count, const unsigned int questions_type, const std::string& admin)
{
	std::lock_guard<std::mutex> lck(_mtx);
	_rooms[_isn] = new Room(_isn, max_players, time_per_question, name, question_count, questions_type, admin);
	return _isn++;
}

void RoomManager::deleteRoom(const unsigned int id)
{
	std::lock_guard<std::mutex> lck(_mtx);
	auto iterator = _rooms.find(id);
	if (iterator == _rooms.end())
		throw std::string("Room not found");
	delete (*iterator).second;
	_rooms.erase(iterator);
}

Room* RoomManager::getRoom(const unsigned int id)
{
	std::lock_guard<std::mutex> lck(_mtx);
	if (_rooms.find(id) == _rooms.end())
		throw std::string("Room not found");
	return _rooms[id];
}

std::vector<Room*> RoomManager::getRooms()
{
	std::vector<Room*> r;
	std::lock_guard<std::mutex> lck(_mtx);
	for (auto& pair : _rooms)
		r.push_back(pair.second);
	return r;
}
