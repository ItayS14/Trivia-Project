#pragma once
#include <string>
class Helper
{
public:

	// return string after padding zeros if necessary
	static std::string getPaddedNumber(int num, int digits);
};