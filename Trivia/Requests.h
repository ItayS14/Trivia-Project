#pragma once

#include <ctime>
#include <vector>


class IRequestHandler
{
public: 
	IRequestHandler() = default;
	virtual ~IRequestHandler() = default;

	virtual bool isRequestRelevant(const Request& request) = 0;
	virtual RequestResult handleRequest(const Request& request) = 0;
};

struct Request
{
	int _request_code;
	std::time_t _recival_time;
	std::string _buffer; // decided to work with strings instead of byte vector as buffer becuase it is easier for the comunicator
};

struct RequestResult
{
	std::string _buffer; // will also include the msg code in it
	IRequestHandler* _new_handler;
}; 