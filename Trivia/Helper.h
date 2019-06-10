#pragma once
#include <string>

#define SIZE_DIGIT_COUNT 4

class Helper
{
public:

	// return string after padding zeros if necessary
	static std::string getPaddedNumber(int num, int digits);
};