#pragma once

#include "IDatabase.h"
#include <vector>

class LoginManager
{
public:

	LoginManager(IDatabase* database) : _database(database) {}
	~LoginManager();
	
	void signup(const std::string username, const std::string password, const std::string email);
	void login(const std::string username, const std::string password);
	void logout(const std::string username); // logout gets user to logout otherwise it makes no sense

private:
	IDatabase* _database;
	std::vector<std::string> _logged_user; // decided to create vector of strings instead of struct that only holds a string
};