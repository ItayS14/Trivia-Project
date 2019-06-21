#include "Room.h"

Room::Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name, unsigned int question_count, const unsigned int questions_type, const std::string& admin) 
	: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _question_count(question_count), _state(JOINABLE), _questions_type(questions_type), _admin(admin)
{
	_users.push_back(admin);
}

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
	if (name == _admin)
		setNewAdmin();
}

void Room::setNewAdmin()
{
	int rand = std::rand() % _users.size(); // getting random index inside the vector
	_admin = _users[rand];
}