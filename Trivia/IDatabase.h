#pragma once

#include <string>

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(const std::string& username,const std::string& password) = 0;
	virtual void addUser(const std::string& username, const std::string& password, const std::string& email) = 0;
};
