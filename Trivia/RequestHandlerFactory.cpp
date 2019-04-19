#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
{
	_login_manager = new LoginManager(database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete _login_manager;
}
