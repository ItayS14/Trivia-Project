#pragma once
#include <WinSock2.h>
#include <vector>
#include "IDatabase.h"
#include "Communicator.h"


class Server
{
public:
	Server(IDatabase* db) { _factory = new RequestHandlerFactory(db); }
	~Server();

	void bindAndListen(int port);

private:
	void startThreadForNewClient();

	SOCKET _server_socket;
	std::vector<Communicator*> _clients;
	RequestHandlerFactory* _factory;
};