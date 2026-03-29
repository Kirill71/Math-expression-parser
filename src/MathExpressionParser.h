#pragma once

#include<memory>
#include <numbers>
#include "Expression.h"

class MathExpressionParser
{
	static constexpr auto PI = std::numbers::pi;
	static constexpr auto E = std::numbers::e;
public:
	std::string eval(const std::string& _exp);
private:
	void factorial(double, std::stack<long double>&);
	const std::string& result_front_view(double, std::string&);
	double calculate_postfix_expression();
	void calculation_inside_stack(std::stack<long double>&, const char*);
	void operation(double&, double&, std::stack<long double>&);
	void operation(double&, std::stack<long double>&);
	bool is_constant(char, std::stack<long double>&);
	double math_function(const std::string&,double);
	void calculate_in_math_functions(std::stack<std::stack<long double>>&, std::stack<std::string>&,const char*);

private:
	std::unique_ptr<Expression> calc_expression = nullptr;
};