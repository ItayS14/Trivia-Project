#pragma once
#include <string>
#include "json.hpp"
#include "RoomManager.h"

#define SIZE_DIGIT_COUNT 4

using json = nlohmann::json;

class Helper
{
public:

	// return string after padding zeros if necessary
	static std::string getPaddedNumber(int num, int digits);
	
	//this function is here to remove code duplication (get room state request is in 2 handlers)
	static json handleGetRoomStateRequest(RoomManager* room_manager, int room_id);
};