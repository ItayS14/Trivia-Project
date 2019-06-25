#pragma once
#include <WinSock2.h>
#include <vector>
#include "IDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	Server(IDatabase* db);
	~Server();

	void bindAndListen(int port);

private:
	void startThreadForNewClient(SOCKET client_socket);

	SOCKET _server_socket;
	std::vector<Communicator*> _clients;
	RequestHandlerFactory* _factory;
};