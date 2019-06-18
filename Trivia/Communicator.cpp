#include "Communicator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <thread>
#include "Helper.h"

Communicator::~Communicator()
{
	if (!_is_closed)
		closesocket(_client_soc);
}

int Communicator::getIntPartFromSocket(int bytes_num)
{
	std::string s = getPartFromSocket(bytes_num);
	int res = std::stoi(s);
	return res;
}

void Communicator::handleRequests()
{
	while (true)
	{
		Request request;
		int code, size;
		std::string msg;
		try
		{
			code = getIntPartFromSocket(3); //This will wait until a new message is recieved anyway
			request._recival_time = std::time(nullptr); //The time won't be really accurate but it's not relevant anyway
			size = getIntPartFromSocket(4);
			msg = getPartFromSocket(size); //And this will clean the socket buffer (unless the sent size is incorrect)
		}
		catch (...) //Client has closed connection
		{
			std::cerr << "Socket error" << std::endl;
			closesocket(_client_soc);
			_is_closed = true;
			return;
		}
		
		request._buffer = std::vector<std::uint8_t>(msg.begin(), msg.end());
		request._request_code = code;

		try
		{
			if (_state->isRequestRelevant(request))
			{
				RequestResult request_result = _state->handleRequest(request);
				if (request_result._new_handler != nullptr && request_result._new_handler != _state) // doesn't delete the current state in case of error or in case of staying in the same state.
				{
					delete _state;
					_state = request_result._new_handler;
				}
				sendData(request_result);
			}
			else
				sendErrorMsg();
		}
		catch (...) //Client has closed connection
		{
			std::cerr << "Error while sending to user!" << std::endl;
			closesocket(_client_soc);
			return;
		}		
	}
}

std::string Communicator::getPartFromSocket(int bytes_num)
{
	if (bytes_num == 0)
		return (char*)"";
	char* data = new char[bytes_num + 1];
	int res = recv(_client_soc, data, bytes_num,0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(_client_soc);
		throw std::exception(s.c_str());
	}
	data[bytes_num] = 0;
	std::string s = std::string(data);
	delete[] data;
	return s;
}

void Communicator::sendData(const RequestResult& request_result)
{
	std::string msg = std::string(request_result._buffer.begin(), request_result._buffer.end());
	const char* data = msg.c_str();
	if (send(_client_soc, data, msg.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}

void Communicator::sendErrorMsg()
{
	std::string msg = "Error: Request does not fit current state!";
	std::string all = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(msg.size(),4) + msg;
	const char* data = all.c_str();
	if (send(_client_soc, data, all.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}
