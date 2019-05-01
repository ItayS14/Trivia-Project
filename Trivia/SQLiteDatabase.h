#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	~SQLiteDatabase() { sqlite3_close(_db); }

	virtual bool doesUserExist(const std::string& username, const std::string& password);
	virtual void addUser(const std::string& username, const std::string& password, const std::string& email);
	//virtual bool isCorrectPassword(const std::string& username, const std::string& password);

	
private:
	sqlite3* _db;
	
	static std::string default_error_msg;

	void initNewDatabase();
	void executeSQL(const std::string& sql_code, const std::string& error_msg = default_error_msg, int(handler)(void*, int, char**, char**) = nullptr, void* argument_for_handler = nullptr);
	static int objectExistsCallBack(void* data, int argc, char** argv, char** azColName);
};