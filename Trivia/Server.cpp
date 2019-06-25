#include "Server.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <thread>
#include <algorithm>

Server::Server(IDatabase * db)
{
	_factory = new RequestHandlerFactory(db);
	_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_server_socket == INVALID_SOCKET)
		throw std::exception("Error initing server!");
}

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
		SOCKET client_socket = accept(_server_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			std::cerr << __FUNCTION__;
		else
		{
			std::thread t(&Server::startThreadForNewClient, this, client_socket); //Creating a thread above the thread that runs the communicator 
			t.detach();															  //so we can clear the communicator's memory when the client disconnects
		}

	}
}

void Server::startThreadForNewClient(SOCKET client_socket)
{
	Communicator* c = new Communicator(client_socket, _factory->createLoginRequestHandler());
	_clients.push_back(c);
	std::thread t(&Communicator::handleRequests, _clients.back());
	t.join();
	_clients.erase(std::find(_clients.begin(), _clients.end(), c));
	delete c;
}