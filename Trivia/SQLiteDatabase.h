#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	virtual ~SQLiteDatabase() = default;
	virtual bool doesUserExist(std::string username) { return false; }
	virtual void addUser(std::string username, std::string password, std::string email) {}
	virtual bool isCorrectPassword(std::string username, std::string password) {}
	
private:
	sqlite3* _db;

};