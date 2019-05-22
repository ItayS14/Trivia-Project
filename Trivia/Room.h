#pragma once
#include <string>
#include <vector>

class Room
{
public:
	Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name, const bool is_active)
		: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _is_active(is_active) {}

	void addUser(const std::string& name);
	void removeUser(const std::string& name);
	std::vector<std::string> getAllUsers();

private:
	unsigned int _id; 
	unsigned int _max_players;
	unsigned int _time_per_question;
	std::string _name;
	bool _is_active;

	std::vector<std::string> _users;
};