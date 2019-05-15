#include "Server.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <thread>

Server::~Server()
{
	for (Communicator* client : _clients)
		delete client;
	delete _factory;
}


void Server::bindAndListen(int port)
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	if (bind(_server_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception("Couldn't bind socket!");

	// Start listening for incoming requests of clients
	if (listen(_server_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception("Couldn't start listening to socket!");
	while (true)
	{
		try
		{
			startThreadForNewClient();
		}
		catch (const std::string& err)
		{
			std::cerr << err;
		}
	}
}

void Server::startThreadForNewClient()
{
	SOCKET client_socket = accept(_server_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	_clients.push_back(new Communicator(client_socket, _factory->createLoginRequestHandler()));
	std::thread t(&Communicator::handleRequests, _clients.back());
	t.detach();
}