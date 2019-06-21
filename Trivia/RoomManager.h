#pragma once

#include "Room.h"
#include <map>

#define MAX_ISN 1000
#define MIN_ISN 10000

class RoomManager
{
public:
	RoomManager(const unsigned int isn) : _isn(isn) {} 
	~RoomManager();

	std::vector<Room*> getRooms();

	int createRoom(const std::string& name, const unsigned int max_players, const unsigned int time_per_question, const unsigned int question_count, const unsigned int questions_type, const std::string& admin);
	void deleteRoom(const unsigned int id);
	Room* getRoom(const unsigned int id);

private:
	unsigned int _isn; // Number that states the id that will be for a new created room (Inited as random number)
	std::map<unsigned int, Room*> _rooms;
};