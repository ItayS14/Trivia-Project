#include "LoginManager.h"
#include <algorithm>

void LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	std::lock_guard<std::mutex> lck(_mtx);
	_database->addUser(username, password, email);
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	if (!_database->doesUserExist(username, password)) // isCorrectPassword also checks if there is a user with the specified username
		throw std::string("Invalid username or password");
	std::lock_guard<std::mutex> lck(_mtx);
	if (std::find(_logged_users.begin(), _logged_users.end(), username) != _logged_users.end())
		throw "Username: " + username + "is already logged to the server";
	_logged_users.push_back(username);
}

void LoginManager::logout(const std::string& username)
{
	std::lock_guard<std::mutex> lck(_mtx);
	auto iterator = std::find(_logged_users.begin(), _logged_users.end(), username);
	if (iterator == _logged_users.end())
		throw "Username: " + username + "is not logged to the server";
	_logged_users.erase(iterator);
}