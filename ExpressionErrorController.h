
#ifndef EXPRESSION_ERROR_CONTROLLER_H
#define EXPRESSION_ERROR_CONTROLLER_H

#include<iostream>
#include<stack>
#include<string>
#include"Definition.h"
#include"UnmatchedBracketsException.h"
#include"UnknownOperatorException.h"
#include"UnknownSintaxException.h"

using std::wstring;
using std::string;
using std::stack;
using std::to_string;

class ExpressionErrorController
{
	static bool is_known_operator(const char);
	static bool is_math_operator(const char);
	static void check_brekets(const string &, size_t);
	static void check_sintax(const string &, size_t);
	static void check_unknown_operators(const string &, size_t);
public:
	static const string& exception_handling(runtime_error&,string&);
	static void check_all_errors(const string &);
	
};
#endif // !EXPRESSION_ERROR_CONTROLLER_H