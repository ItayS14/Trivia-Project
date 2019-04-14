#pragma once
#include "IDatabase.h"

class SQLiteDatabase : public IDatabase
{
	virtual bool doesUserExist(std::string username) { return false; }
	virtual void addUser(std::string username, std::string password, std::string email) {}
};