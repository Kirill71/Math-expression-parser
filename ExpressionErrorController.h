
#ifndef EXPRESSION_ERROR_CONTROLLER_H
#define EXPRESSION_ERROR_CONTROLLER_H

#include<iostream>
#include<stack>
#include<string>
#include"Definition.h"
#include"UnmatchedBracketsException.h"
#include"UnknownOperatorException.h"
#include"UnknownSyntaxException.h"

using std::wstring;
using std::string;
using std::stack;
using std::to_string;

class ExpressionErrorController
{
	static bool is_known_operator(const char);
	static bool is_operator(const char);
	static bool is_math_operator(const char);
public:
	static const string& exception_handling(const runtime_error&,string&);
	static void check_all_errors(const string &);
	static bool is_math_operator_or_fuctorial_op_persent(const char);
};
#endif // !EXPRESSION_ERROR_CONTROLLER_H