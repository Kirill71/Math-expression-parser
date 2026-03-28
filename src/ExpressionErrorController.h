#pragma once

#include<string>
#include <stdexcept>

class ExpressionErrorController
{
	static bool is_known_operator(char);
	static bool is_operator(char);
	static bool is_math_operator(char);
public:
	static const std::string& exception_handling(const std::runtime_error&, std::string&);
	static void check_all_errors(const std::string &);
	static bool is_math_operator_or_factorial_or_percent(char);
};