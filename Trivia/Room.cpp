#include "Room.h"

void Room::addUser(const std::string& name)
{
	if (std::find(_users.begin(), _users.end(), name) != _users.end())
		throw "User is already logged to room " + std::to_string(_id);
	_users.push_back(name);
}

void Room::removeUser(const std::string& name)
{
	auto iterator = std::find(_users.begin(), _users.end(), name);
	if (iterator == _users.end())
		throw "Username: " + name + "is not logged to room " + std::to_string(_id);
	_users.erase(iterator);
}

std::vector<std::string> Room::getAllUsers()
{
	return _users;
}