#pragma once
#include <string>
#include <vector>

enum RoomStates
{
	JOINABLE = 0,
	IN_GAME,
	FINISHED
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
		: _id(id), _max_players(max_players), _time_per_question(time_per_question), _name(name), _question_count(question_count), _state(JOINABLE), _questions_type(questions_type) {}
	Room() = default;

	void addUser(const std::string& name);
	void removeUser(const std::string& name);

	const std::vector<std::string>& getAllUsers() { return _users; }
	size_t getNumberOfLoggedUsers() { return _users.size(); }

	unsigned int _id; // those members are public becuase it's useless to set them as private and set getters and setters for each one of them.
	unsigned int _max_players;
	unsigned int _time_per_question;
	unsigned int _question_count;
	unsigned int _questions_type;
	unsigned int _state;
	std::string _name;

private:
	std::vector<std::string> _users;
};
