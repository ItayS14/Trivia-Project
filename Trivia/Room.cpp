#include "Room.h"

Room::Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name, unsigned int question_count, const unsigned int questions_type, const std::string& admin) 
	: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _question_count(question_count), _state(JOINABLE), _questions_type(questions_type), _admin(admin), _start_time(0)
{
	_users.push_back(admin);
}

const std::vector<std::string>& Room::getAllUsers()
{
	std::lock_guard<std::mutex> lck(_users_mtx);
	return _users;
}

size_t Room::getNumberOfLoggedUsers()
{
	std::lock_guard<std::mutex> lck(_users_mtx);
	return _users.size();
}

void Room::addUser(const std::string& name)
{
	std::lock_guard<std::mutex> lck(_users_mtx);
	if (std::find(_users.begin(), _users.end(), name) != _users.end())
		throw std::string("User is already logged to the room");
	if (_users.size() > _max_players)
		throw std::string("Room is full");
	_users.push_back(name);
}

void Room::removeUser(const std::string& name)
{
	std::lock_guard<std::mutex> lck(_users_mtx);
	auto iterator = std::find(_users.begin(), _users.end(), name);
	if (iterator == _users.end())
		throw std::string("User is not logged to the room");
	_users.erase(iterator);
	if (name == _admin && _users.size() > 0) // new admin will be the first user in the list
		_admin = _users[0];
}


void Room::setState(const unsigned int state)
{
	std::lock_guard<std::mutex> lck(_state_mtx);
	_state = state;
}

unsigned int Room::getState()
{
	std::lock_guard<std::mutex> lck(_state_mtx);
	return _state;
}