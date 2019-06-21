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
	Room(const unsigned int id, const unsigned int max_players, const unsigned int time_per_question, const std::string& name,
		unsigned int question_count, const unsigned int questions_type, const std::string& admin);

	void addUser(const std::string& name);
	void removeUser(const std::string& name);

	const std::vector<std::string>& getAllUsers() { return _users; }
	size_t getNumberOfLoggedUsers() { return _users.size(); }

	const unsigned int _id; // those members are public becuase it's useless to set them as private and set getters and setters for each one of them.
	const unsigned int _max_players;
	const unsigned int _time_per_question;
	const unsigned int _question_count;
	const unsigned int _questions_type;
	unsigned int _state;
	const std::string _name;

private:
	void setNewAdmin(); // The function will get a random new user for the room

	std::string _admin;
	std::vector<std::string> _users;
};
