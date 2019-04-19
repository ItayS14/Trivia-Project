#include <fstream>
#include <iostream>
#include "SQLiteDatabase.h"

#define NAME "Trivia.sqlite"

//SQLite database constructor. Creates a new database if it doesn't exist already.
SQLiteDatabase::SQLiteDatabase()
{
	bool exists = doesFileExist(NAME);
	int res = sqlite3_open(NAME, &_db);
	if (res != SQLITE_OK)
		throw std::exception("Failed to open database!");
	if (!exists) //check if database already exists, if not create a new one
		initNewDatabase();
}

//A log-in function, checks if there's a user with the specified username.
bool SQLiteDatabase::doesUserExist(const std::string & username)
{
	std::string command = "SELECT * FROM users WHERE username = \"" + username + "\"";
	bool b = false;
	int res = sqlite3_exec(_db, command.c_str(), userExistsCallback, &b, nullptr);
	if (res != SQLITE_OK)
		throw std::exception(sqlite3_errmsg(_db));
	return b;
}

//Signup function
void SQLiteDatabase::addUser(const std::string & username, const std::string & password, const std::string & email)
{
	std::string command = "INSERT INTO users VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	int res = sqlite3_exec(_db, command.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
		throw std::exception("Failed to sign up user!");
}

bool SQLiteDatabase::isCorrectPassword(const std::string & username, const std::string & password)
{
	std::string command = "SELECT * FROM users WHERE username = \"" + username + "\" AND password = \"" + password + "\"";
	std::cout << command << std::endl;
	bool b = false;
	int res = sqlite3_exec(_db, command.c_str(), userExistsCallback, &b, nullptr);
	if (res != SQLITE_OK)
		throw std::exception(sqlite3_errmsg(_db));
	return b;
}

//Simple function to check if file with the specified name exists
bool SQLiteDatabase::doesFileExist(const std::string& name)
{
	std::ifstream file(name.c_str());
	return file.good();
}

//Create the tables and check that the database was created successfully
void SQLiteDatabase::initNewDatabase()
{
	int res1, res2, res3;
	res1= sqlite3_exec(_db, "CREATE TABLE \"Users\" ( 'username' TEXT NOT NULL, 'password' TEXT NOT NULL, 'email' TEXT NOT NULL, PRIMARY KEY('username') )", nullptr, nullptr, nullptr);
	res2 = sqlite3_exec(_db, "CREATE TABLE \"Questions\" ( 'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'question' TEXT NOT NULL, 'correct_ans' TEXT NOT NULL, 'ans2' TEXT NOT NULL, 'ans3' TEXT NOT NULL, 'ans4' TEXT NOT NULL )", nullptr, nullptr, nullptr);
	res3 = sqlite3_exec(_db, "CREATE TABLE \"Games\" ( 'game_id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'status' INTEGER NOT NULL, 'start_time' TEXT NOT NULL, 'end_time' TEXT NOT NULL )", nullptr, nullptr, nullptr);
	if (res1 != SQLITE_OK || res2 != SQLITE_OK || res3 != SQLITE_OK)
		throw std::exception("Failed to create database!");
}

//If this callback is called, it means sqlite have found a user with the specified username
int SQLiteDatabase::userExistsCallback(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}
