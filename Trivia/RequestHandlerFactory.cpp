#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
{
	_login_manager = new LoginManager(database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete _login_manager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(_login_manager, this);
}
