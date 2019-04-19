#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SQLiteDatabase : public IDatabase
{
public:
	 SQLiteDatabase();
	 ~SQLiteDatabase() { sqlite3_close(_db); }
	
	virtual bool doesUserExist(const std::string& username);
	virtual void addUser(const std::string& username, const std::string& password, const std::string& email);
	virtual bool isCorrectPassword(const std::string& username, const std::string& password);
	
private:
	sqlite3* _db;
	
	bool doesFileExist(const std::string& name);
	void initNewDatabase();
	
	static int userExistsCallback(void* data, int argc, char** argv, char** azColName);
};