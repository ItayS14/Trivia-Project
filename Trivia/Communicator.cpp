#include "Communicator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <thread>
#include "Helper.h"

Communicator::Communicator(SOCKET clientSoc, IRequestHandler* state)
{
	this->clientSoc = clientSoc;
	this->_state = state; //This will always be login state since it's the first request
}

Communicator::~Communicator()
{
	closesocket(clientSoc);
}

int Communicator::getIntPartFromSocket(int bytesNum)
{
	char* s = getPartFromSocket(bytesNum);
	int res = atoi(s);
	delete s;
	return res;
}

// recieve data from socket according byteSize
// returns the data as string
std::string Communicator::getStringPartFromSocket(int bytesNum)
{
	char* s  = getPartFromSocket(bytesNum);
	std::string res(s);
	delete s;
	return res;
}


void Communicator::handleRequests()
{
	while (true)
	{
		Request request;
		
		int code = getIntPartFromSocket(3); //This will wait until a new message is recieved anyway
		request._recival_time = std::time(nullptr); //The time won't be really accurate but it's not relevant anyway
		int size = getIntPartFromSocket(4);
		std::string msg = getStringPartFromSocket(size); //And this will clean the socket buffer (unless the sent size is incorrect)
		
		request._buffer = std::vector<std::uint8_t>(msg.begin(), msg.end());
		request._request_code = code;

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

}

char* Communicator::getPartFromSocket(int bytesNum)
{
	if (bytesNum == 0)
		return (char*)"";
	char* data = new char[bytesNum + 1];
	int res = recv(clientSoc, data, bytesNum,0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(clientSoc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	return data;
}

void Communicator::sendData(const RequestResult& request_result)
{
	std::string msg = std::string(request_result._buffer.begin(), request_result._buffer.end());
	const char* data = msg.c_str();
	if (send(clientSoc, data, msg.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}

void Communicator::sendErrorMsg()
{
	std::string code = "400";
	std::string msg = "Error: Request does not fit current state!";
	std::string all = code + Helper::getPaddedNumber(msg.size(),4) + msg;
	const char* data = all.c_str();
	if (send(clientSoc, data, msg.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}
