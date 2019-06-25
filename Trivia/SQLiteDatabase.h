#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <mutex>

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	~SQLiteDatabase() { sqlite3_close(_db); }

	bool doesUserExist(const std::string& username, const std::string& password) override;
	void addUser(const std::string& username, const std::string& password, const std::string& email) override;
	std::vector<Question*> getQuestions(const int& question_count,const int& type) override;
private:
	sqlite3* _db;
	std::mutex mtx;
	static std::string default_error_msg;

	void initNewDatabase();
	void executeSQL(const std::string& sql_code, const std::string& error_msg = default_error_msg, int(handler)(void*, int, char**, char**) = nullptr, void* argument_for_handler = nullptr);
	//Callbacks must be static for some reason
	static int objectExistsCallBack(void* data, int argc, char** argv, char** azColName);
	static int getQuestionsCallback(void* data, int argc, char** argv, char** azColName);
	bool isEmailValid(const std::string& email);
};