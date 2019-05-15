#pragma once

#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;
// every handler the factory makes is allocated on the heap therefore needs to be deleted later
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler(); 

private:
	LoginManager* _login_manager;
};