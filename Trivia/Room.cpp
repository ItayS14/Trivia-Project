#include "Room.h"

void Room::addUser(const std::string& name)
{
	if (std::find(_users.begin(), _users.end(), name) != _users.end())
		throw std::string("User is already logged to the room");
	if (_users.size() > _max_players)
		throw std::string("Room is full");
	_users.push_back(name);
}

void Room::removeUser(const std::string& name)
{
	auto iterator = std::find(_users.begin(), _users.end(), name);
	if (iterator == _users.end())
		throw std::string("User is not logged to the room");
	_users.erase(iterator);
}

