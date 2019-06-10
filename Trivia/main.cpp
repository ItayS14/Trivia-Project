#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include "LoginManager.h"
#include "json.hpp"
#include "SQLiteDatabase.h"
#include "RequestHandlerFactory.h"

using json = nlohmann::json;

int main()
{
	WSAInitializer wsaInit;
	SQLiteDatabase* db = new SQLiteDatabase();
	Server myServer(db);

	myServer.bindAndListen(4422);

	delete db;
	system("pause");
	return 0;
}
