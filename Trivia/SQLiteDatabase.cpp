#include <fstream>
#include <iostream>
#include <regex>
#include "SQLiteDatabase.h"

#define NAME "Trivia.sqlite"
#define NUM_OF_QUESTIONS 4

std::string SQLiteDatabase::default_error_msg = "Error accessing database!";

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
bool SQLiteDatabase::doesUserExist(const std::string& username, const std::string& password)
{
	std::string command = "SELECT * FROM users WHERE username = \"" + username + "\" AND password = \"" + password + "\"";
	bool b = false;
	executeSQL(command, default_error_msg, objectExistsCallBack, &b);
	return b;
}

//Signup function
void SQLiteDatabase::addUser(const std::string& username, const std::string& password, const std::string& email)
{
	if (!isEmailValid(email))
		throw std::string("Email is not valid!");
	std::string command = "INSERT INTO users VALUES (\"" + username + "\", \"" + password + "\", \"" + email + "\");";
	executeSQL(command, "Username: '" + username + "' already used!");
}

std::vector<Question*> SQLiteDatabase::getQuestions(const int& question_count, const int& type)
{
	std::string command = "SELECT question,correct_ans,ans2,ans3,ans4 FROM questions WHERE type = " + std::to_string(type) + " ORDER BY RANDOM() LIMIT " + std::to_string(question_count) + "; ";
	std::vector<Question*> questions;
	executeSQL(command, default_error_msg, getQuestionsCallback, &questions);
	return questions;
}

//Create the tables and check that the database was created successfully
void SQLiteDatabase::initNewDatabase()
{
	sqlite3_open(NAME, &_db);
	executeSQL("CREATE TABLE 'Users' ( 'username' TEXT NOT NULL, 'password' TEXT NOT NULL, 'email' TEXT NOT NULL, PRIMARY KEY('username') )");
	executeSQL("CREATE TABLE 'Questions' ('id'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,'question' TEXT NOT NULL,'type' INTEGER NOT NULL,'correct_ans' TEXT NOT NULL,'ans2'	TEXT NOT NULL,'ans3' TEXT NOT NULL,'ans4' TEXT NOT NULL); ");
	executeSQL("CREATE TABLE 'Games' ( 'game_id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'status' INTEGER NOT NULL, 'start_time' TEXT NOT NULL, 'end_time' TEXT NOT NULL )");
	system("pythonw DatabaseFiller.py"); //Fill the database with questions. Assuming the server python installed.
}

//If this callback is called, it means sqlite have found a user with the specified username
int SQLiteDatabase::objectExistsCallBack(void* data, int argc, char** argv, char** azColName)
{
	*(bool*)data = true;
	return 0;
}

int SQLiteDatabase::getQuestionsCallback(void * data, int argc, char ** argv, char ** azColName)
{
	std::vector<std::string> answers = { argv[2],argv[3],argv[4] };
	int correct_ans = std::rand() % NUM_OF_QUESTIONS;
	answers.insert(answers.begin() + correct_ans, argv[1]);
	((std::vector<Question*>*)data)->push_back(new Question(argv[0], answers, correct_ans));
	return 0;
}

bool SQLiteDatabase::isEmailValid(const std::string & email)
{
	//Credit to: https://stackoverflow.com/questions/36903985/email-validation-in-c
	// define a regular expression
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	// try to match the string with the regular expression
	return std::regex_match(email, pattern);

}

void SQLiteDatabase::executeSQL(const std::string& sql_code, const std::string& error_msg, int(handler)(void*, int, char**, char**), void* argument_for_handler)
{
	std::lock_guard<std::mutex> lock_guard(mtx);
	if (sqlite3_exec(_db, sql_code.c_str(), handler, argument_for_handler, nullptr) != SQLITE_OK)
		throw std::string(error_msg);
}
