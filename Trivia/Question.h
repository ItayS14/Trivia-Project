#pragma once
#include <string>
#include <vector>

struct Question
{
	Question(const std::string & question, const std::vector<std::string>& answers, const int correct_ans) : _question(question), _answers(answers), _correct_ans(correct_ans) {}

	std::string _question;
	std::vector<std::string> _answers;
	unsigned int _correct_ans; //index of correct answer
};