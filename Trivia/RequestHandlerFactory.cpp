#include "RequestHandlerFactory.h"

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete _login_manager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(_login_manager, this);
}
