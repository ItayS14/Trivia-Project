#pragma once

#include <ctime>
#include <vector>
#include <cstdint>


struct RequestResult;
struct Request;

enum Codes
{
	SIGNUP = 100,
	LOGIN,
	LOGOUT,
	CREATE_ROOM,
	JOIN_ROOM,
	GET_ROOMS,
	GET_ROOM_STATE,
	LEAVE_ROOM,
	START_GAME,
	GET_QUESTION,
	SUBMIT_ANSWER,
	GET_STATISTICS,
	GET_LEADERBOARD,
	LEAVE_GAME,
	SUCCESS = 200,
	ERROR_MSG = 400
};

class IRequestHandler
{
public: 
	IRequestHandler() = default;
	virtual ~IRequestHandler() = default;

	virtual bool isRequestRelevant(const Request& request) = 0;
	virtual RequestResult handleRequest(const Request& request) = 0;
	virtual void handleSocketError() = 0;
};

struct Request
{
	int _request_code;
	std::time_t _recival_time;
	std::vector<std::uint8_t> _buffer; // the buffer holds only the json
};

struct RequestResult
{
	std::vector<std::uint8_t> _buffer; // will also include the msg code in it
	IRequestHandler* _new_handler;
}; 