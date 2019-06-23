#include "Question.h"
#include <random>
#include <ctime>

#define NUM_OF_QUESTIONS 4

Question::Question(const std::string & question, const std::string & correct_ans, const std::string & ans2, const std::string & ans3, const std::string & ans4) :_question(question)
{
	_answers.push_back(ans2);
	_answers.push_back(ans3);
	_answers.push_back(ans4);
	_correct_ans = std::rand() % NUM_OF_QUESTIONS;
	_answers.insert(_answers.begin() + _correct_ans, correct_ans); //Insert the correct answer at a random place
}
