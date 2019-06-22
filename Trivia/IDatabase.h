#pragma once

#include <string>
#include <vector>
#include "Question.h"
class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(const std::string& username, const std::string& password) = 0;
	virtual void addUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual std::vector<Question*> getQuestions(const int& question_count, const int& type) = 0;
};
