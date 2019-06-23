#pragma once
#include <string>
#include <vector>

struct Question
{
	Question(const std::string& question, const std::string& correct_ans, const std::string& ans2, const std::string& ans3, const std::string& ans4);

	std::string _question;
	std::vector<std::string> _answers;
	int _correct_ans; //index of correct answer
};