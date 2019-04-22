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
	RequestResult signup(const Request& request);
	RequestResult login(const Request& request);

	LoginManager* _login_manager;
	RequestHandlerFactory* _handler_factory; 
};