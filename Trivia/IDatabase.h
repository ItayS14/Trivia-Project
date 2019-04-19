#pragma once

#include <string>

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(std::string username) = 0;
	virtual void addUser(std::string username, std::string password, std::string email) = 0;
	virtual bool isCorrectPassword(std::string username, std::string password) = 0;
	
};
