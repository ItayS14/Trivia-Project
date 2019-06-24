#pragma once

#include "IDatabase.h"
#include <vector>
#include <mutex>

class LoginManager
{
public:
	LoginManager(IDatabase* database) : _database(database) {}
	~LoginManager() = default;
	
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username); // changed logout, now gets string (username) to logout otherwise it makes no sense

private:
	IDatabase* _database;
	std::vector<std::string> _logged_users; // decided to create vector of strings instead of struct that only holds a string
	std::mutex _mtx;
};