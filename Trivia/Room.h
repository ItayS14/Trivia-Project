#pragma once
#include <string>
#include <vector>

enum RoomStates
{
	START = 0,
	RUN,
	END
};

enum QuestionType
{
	ALL = 0,
	SPORT,
	GENERAL,
	MATH,
	TV,
	GEOGRAPHY
};

class Room
{
public:
	Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name, unsigned int question_count, const unsigned int questions_type)
		: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _question_count(question_count), _state(START), _questions_type(questions_type) {}
	Room() = default;

	void addUser(const std::string& name);
	void removeUser(const std::string& name);

	const std::vector<std::string>& getAllUsers() { return _users; }
	unsigned int getState() { return _state; }
	size_t getNumberOfLoggedUsers() { return _users.size(); }

	unsigned int _id; 
	unsigned int _max_players;
	unsigned int _time_per_question;
	unsigned int _question_count;
	unsigned int _questions_type;
	std::string _name;

private:
	unsigned int _state;
	std::vector<std::string> _users;
};