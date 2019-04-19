#pragma once

#include <string>

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual void addUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual bool isCorrectPassword(const std::string& username, const std::string& password) = 0;
	
};
