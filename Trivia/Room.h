#pragma once
#include <string>
#include <vector>

enum RoomStates
{
	START = 0,
	RUN,
	END
};

class Room
{
public:
	Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name, unsigned int question_count)
		: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _question_count(question_count), _state(START) {}

	void addUser(const std::string& name);
	void removeUser(const std::string& name);

	const std::vector<std::string>& getAllUsers() { return _users; }
	unsigned int getState() { return _state; }
	size_t getNumberOfLoggedUsers() { return _users.size(); }

	unsigned int _id; 
	unsigned int _max_players;
	unsigned int _time_per_question;
	unsigned int _question_count;
	std::string _name;

private:
	unsigned int _state;
	std::vector<std::string> _users;
};