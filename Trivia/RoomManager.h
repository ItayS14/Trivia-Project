#pragma once

#include "Room.h"
#include <map>

#define MAX_ISN 1000
#define MIN_ISN 10000

class RoomManager
{
public:
	RoomManager() : _isn(0) {} // todo: get random isn
	
	std::vector<Room> getRooms();

	void createRoom(const std::string& name, const unsigned int max_players, const unsigned int time_per_question, const bool is_active);
	void deleteRoom(const unsigned int id);
	bool getRoomState(const unsigned int id);

private:
	int _isn; // Number that states the id that will be for a new created room (Inited as random number)
	std::map<unsigned int, Room> _rooms;
};