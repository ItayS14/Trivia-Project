#pragma once

#include <string>

class IDatabase
{
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool addUser(std::string username, std::string password, std::string email) = 0;
};
