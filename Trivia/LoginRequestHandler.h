#pragma once

#include "Requests.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : IRequestHandler
{
public:
	LoginRequestHandler(LoginManager* login_manager, RequestHandlerFactory* handler_factory) : _login_manager(login_manager), _handler_factory(handler_factory) {}
	virtual ~LoginRequestHandler() = default;

	virtual bool isRequestRelevant(const Request& request);
	virtual RequestResult handleRequest(const Request& request);

private:
	//removed login and signup function becuase while i wrote them there was a code duplication that code easily be avoided when merging the functions
	LoginManager* _login_manager;
	RequestHandlerFactory* _handler_factory; 
};