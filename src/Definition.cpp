#include "Definition.h"
#include <string>

bool is_alpha(const char symbol)
{
	return symbol >= ALPHABET_BEGIN && symbol <= ALPHABET_END;
}

bool is_point(const char symbol)
{
	return symbol == POINT || symbol == COMA;
}

bool is_digit(const char* str)
{
	const std::string str1(str), str2("0");

	if (str1 == str2)
		return true;
	return atof(str) ? true : false;
}