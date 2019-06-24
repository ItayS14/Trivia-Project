#pragma once
#include <string>
#include <vector>
#include <mutex>

enum RoomStates
{
	JOINABLE = 0,
	IN_GAME,
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

	const std::vector<std::string>& getAllUsers();
	size_t getNumberOfLoggedUsers();
	
	unsigned int getState(); // the reason there is getters and setters for state is to defend it with mutex
	void setState(const unsigned int state);

	const unsigned int _id; // those members are public becuase it's useless to set them as private and set getters and setters for each one of them.
	const unsigned int _max_players;
	const unsigned int _time_per_question;
	const unsigned int _question_count;
	const unsigned int _questions_type;
	const std::string _name;
	std::string _admin;
	time_t _start_time;

private:
	std::vector<std::string> _users;
	std::mutex _state_mtx;
	std::mutex _users_mtx;
	unsigned int _state;
};
