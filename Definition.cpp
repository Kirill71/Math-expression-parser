#include "Definition.h"
#include<iostream>
#include<string>

using std::string;
using std::prev;
bool is_alpha(const char simbol)
{
	return (simbol >= ALPHABET_BEGIN && simbol <= ALPHABET_END) ? true : false;
}

bool is_point(const char simbol)
{
	return (simbol == POINT || simbol == COMA) ? true : false;
}

bool is_digit(const char simbol)
{
	return (simbol != Ï&&isdigit(simbol));
}

bool is_digit(const char* str)
{
	string str1(str),str2("0");

	if (str1==str2)
		return true;
	return atof(str) ? true : false;
}

bool is_digit_or_alpha(const string::const_iterator & pos)
{
	return(isalnum(*pos)) ? true : false;
}

bool is_operator(const string::const_iterator & pos)
{
	return (*pos == ADDITION || *pos == DEDACTION || *pos == MULTIPLE || *pos == DIVISION || *pos==POWER || *pos== FACTORIAL || *pos==PERSENT) ? true : false;
}

bool is_bracket(const string::const_iterator & pos)
{
	return (*pos == LEFT_BRACKET || *pos == RIGHT_BRACKET ) ? true : false;
}

size_t group_number(const string::const_iterator & pos)
{
	if (is_digit_or_alpha(pos)) return 1;
	if (is_operator(pos)) return is_unary_minus(pos) ? 1 : 2;
	if (is_bracket(pos)) return 3;
	return ERROR_FAILURE;
}

bool is_unary_minus(const string::const_iterator & pos)
{
	return (*pos == DEDACTION && (*pos == 0 || *prev(pos)== LEFT_BRACKET || is_operator(prev(pos)))) ? true : false;
}

size_t simbol_type(const string::const_iterator & pos)
{
	switch (group_number(pos))
	{
	case 1: {return 1; }
	case 2: {return 2; }
	case 3: {return 3;}
	}
	return ERROR_FAILURE;
}

