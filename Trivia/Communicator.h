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
	Communicator(SOCKET clientSoc, IRequestHandler* state);
	~Communicator();
	void handleRequests();

	
	
private:
	SOCKET clientSoc;
	char* getPartFromSocket(int bytesNum);
	int getIntPartFromSocket(int bytesNum);
	std::string getStringPartFromSocket(int bytesNum);
	void sendData(const RequestResult& request_result);
	void sendErrorMsg();
	IRequestHandler* _state;
};
