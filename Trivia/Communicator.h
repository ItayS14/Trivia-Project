#pragma once

#include <vector>
#include <map>
#include <string>
#include <WinSock2.h>
#include "SQLiteDatabase.h"
#include "Requests.h"


class Communicator
{
public:
	Communicator(SOCKET client_soc, IRequestHandler* state) : _client_soc(client_soc), _state(state) {}
	~Communicator();
	void handleRequests();

	
	
private:
	SOCKET _client_soc;
	IRequestHandler* _state; // will always be login handler at start

	std::string getPartFromSocket(int bytes_num);
	int getIntPartFromSocket(int bytes_num);
	void sendData(const RequestResult& request_result);
	void sendErrorMsg();

};
