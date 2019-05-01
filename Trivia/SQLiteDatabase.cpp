#include <fstream>
#include <iostream>
#include "SQLiteDatabase.h"

#define NAME "Trivia.sqlite"

//SQLite database constructor. Creates a new database if it doesn't exist already.
SQLiteDatabase::SQLiteDatabase()
{
	int res = sqlite3_open_v2(NAME, &_db, SQLITE_OPEN_READWRITE, NULL); //check if database already exists, if not create a new one
	if (res == SQLITE_CANTOPEN)
		initNewDatabase();
	else if (res != SQLITE_OK)
		throw std::exception("Failed to open database!");

}

//A log-in function, checks if there's a user with the specified username.
bool SQLiteDatabase::doesUserExist(const std::string & username)
{
	std::string command = "SELECT * FROM users WHERE username = \"" + username + "\"";
	bool b = false;
	executeSQL(command.c_str(), objectExistsCallBack, &b);
	return b;
}

//Signup function
void SQLiteDatabase::addUser(const std::string & username, const std::string & password, const std::string & email)
{
	std::string command = "INSERT INTO users VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	executeSQL(command);
}

bool SQLiteDatabase::isCorrectPassword(const std::string & username, const std::string & password)
{
	std::string command = "SELECT * FROM users WHERE username = \"" + username + "\" AND password = \"" + password + "\"";
	bool b = false;
	executeSQL(command, objectExistsCallBack, &b);
	return b;
}

//Create the tables and check that the database was created successfully
void SQLiteDatabase::initNewDatabase()
{
	sqlite3_open(NAME, &_db);
	executeSQL("CREATE TABLE \"Users\" ( 'username' TEXT NOT NULL, 'password' TEXT NOT NULL, 'email' TEXT NOT NULL, PRIMARY KEY('username') )");
	executeSQL("CREATE TABLE \"Questions\" ( 'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'question' TEXT NOT NULL, 'correct_ans' TEXT NOT NULL, 'ans2' TEXT NOT NULL, 'ans3' TEXT NOT NULL, 'ans4' TEXT NOT NULL )");
	executeSQL("CREATE TABLE \"Games\" ( 'game_id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'status' INTEGER NOT NULL, 'start_time' TEXT NOT NULL, 'end_time' TEXT NOT NULL )");
}

//If this callback is called, it means sqlite have found a user with the specified username
int SQLiteDatabase::objectExistsCallBack(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}

void SQLiteDatabase::executeSQL(const std::string& sql_code, int(handler)(void*, int, char**, char**), void* argument_for_handler)
{
	if (sqlite3_exec(_db, sql_code.c_str(), handler, argument_for_handler, nullptr) != SQLITE_OK)
		throw std::string("Error while connecting to database!");
}
