#include "MathExpressionParser.h"
#include "MathExpressionException.h"
#include "ExpressionErrorController.h"
#include "Definition.h"

#include <cstring>
#include <cmath>

std::string MathExpressionParser::eval(const std::string& _exp)
{
	double numeric_result{};
	std::string result{};
	try
	{
		calc_expression = std::make_unique<Expression>(_exp);
		ExpressionErrorController::check_all_errors(calc_expression->get_infix_expression());
		calc_expression->convert_from_infix_to_postfix_notation();
	}
	catch (const UnmatchedBracketsException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (const UnknownSyntaxException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (const UnknownOperatorException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	try
	{
		numeric_result = this->calculate_postfix_expression();
	}
	catch (const DivideByZeroException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (const NegativeValueInLogarithmicFunctionException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (const NegativeValueInSquareRootFunctionException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	
	return result_front_view(numeric_result, result);
}

void MathExpressionParser::factorial(const double op2, std::stack<long double>& stack)
{
	const bool is_negative = op2 < 0;
	const double magnitude = std::fabs(op2);
	long long factorial{1};
	for (size_t i = 1; i <= static_cast<size_t>(magnitude); ++i)
		factorial *= static_cast<long long>(i);
	stack.push(is_negative ? -factorial : factorial);
}

const std::string & MathExpressionParser::result_front_view(const double numeric_result, std::string& front_view)
{
	const double remainder = numeric_result - static_cast<int>(numeric_result);
	if (remainder <= std::numeric_limits<double>::epsilon())
	{
		front_view = std::move(std::to_string(static_cast<int>(numeric_result)));
	}
	else
	{
		front_view = std::move(std::to_string(static_cast<float>(numeric_result)));
	}
	front_view.shrink_to_fit();
	return front_view;
}

double MathExpressionParser::calculate_postfix_expression()
{
	bool is_only_arithmetic_expression(true);
	std::stack<std::string> math_functions_stack;
	std::stack<std::stack< long double>> current_math_function_calculate_stack;
	std::stack<long double> stack;
	const char* token=std::strtok(const_cast<char*>(calc_expression->get_postfix_expression().c_str()),SPACE_C_STR);
	while (token != nullptr)
	{
		if (is_alpha(token[0]) && token[0] != e_num) {math_functions_stack.push(token);current_math_function_calculate_stack.push(stack);}
		else
		{
			if (is_only_arithmetic_expression) { current_math_function_calculate_stack.push(stack); is_only_arithmetic_expression = false; }
		}
		is_constant(token[0], current_math_function_calculate_stack.top());
		if (is_digit(token))  current_math_function_calculate_stack.top().push(std::stof(token));
		else
		{
			if (token[0] == RIGHT_FUNCTION_BRACKET) 
			{
				calculate_in_math_functions(current_math_function_calculate_stack, math_functions_stack, token);
			}
			else
			{
				if (ExpressionErrorController::is_math_operator_or_factorial_or_percent(token[0])) calculate_in_math_functions(current_math_function_calculate_stack, math_functions_stack, token);
			}
		}
		token = std::strtok(nullptr, SPACE_C_STR);
	}
	return static_cast<double>(current_math_function_calculate_stack.top().top());
}

void MathExpressionParser::calculation_inside_stack(std::stack<long double>&stack, const char *token)
{
	double op1(0), op2(0);
	if (token[0] == FACTORIAL || token[0] == PERCENT) operation(op2, stack);
	else	operation(op1, op2, stack);
	switch (token[0])
	{
		case ADDITION: { stack.push(op1 + op2); break;}
		case DEDUCTION: {stack.push(op1 - op2); break;}
		case MULTIPLE: { stack.push(op1 * op2); break;}
		case DIVISION: {if (op2 == 0.0) throw DivideByZeroException(); stack.push(op1 / op2); break; }
		case POWER: {stack.push(pow(op1, op2)); break;}
		case FACTORIAL: {factorial(op2, stack); break;}
		case PERCENT: { stack.push(stack.empty() ? op2 / 100.0 : static_cast<double>(stack.top()) * op2 / 100.0); break; }
		default:;
	}
}

void  MathExpressionParser::operation(double& op1, double& op2, std::stack<long double>& stack)
{
	operation(op2, stack);
	op1 = static_cast<double>(stack.top());
	stack.pop();
}

void MathExpressionParser::operation(double &op2, std::stack<long double>& stack)
{
	op2 = static_cast<double>(stack.top());
	stack.pop();
}

bool MathExpressionParser::is_constant(const char symbol, std::stack<long double>&stack)
{
	if (symbol == e_num) {stack.push(E); return true;}
	if (symbol== p_num){stack.push(PI); return true;}
	return false;
}

double MathExpressionParser::math_function(const std::string & math_func_str, const double value)
{
	const double radian_value = value * PI / 180;
	if (math_func_str == SIN) return std::sin(radian_value);
	if (math_func_str == COS) return std::cos(radian_value);
	if (math_func_str == TAN) return std::tan(radian_value);
	if (math_func_str == CTAN) return 1.0 / std::tan(radian_value);
	if (math_func_str == SQRT) { if (value < 0.0) throw NegativeValueInSquareRootFunctionException(); return std::sqrt(value);}
	if (math_func_str == LN) { if (value < 0.0) throw NegativeValueInLogarithmicFunctionException(); return std::log(value);}
	if (math_func_str == LG) { if (value < 0.0) throw NegativeValueInLogarithmicFunctionException(); return std::log10(value);}
	if (math_func_str == LOGB) { if (value < 0.0) throw NegativeValueInLogarithmicFunctionException(); return std::log2(value); }
	if (math_func_str == ABS) return std::fabs(value);
	if (math_func_str == ASIN) return std::asin(radian_value);
	if (math_func_str == ACOS) return std::acos(radian_value);
	if (math_func_str == ATAN) return std::atan(radian_value);
	if (math_func_str == ACTAN) return 1.0 / std::atan(radian_value);
	if (math_func_str == SINH) return std::sinh(radian_value);
	if (math_func_str == COSH) return std::cosh(radian_value);
	if (math_func_str == TANH) return std::tanh(radian_value);
	if (math_func_str == CTANH) return 1.0/std::tanh(radian_value);
	if (math_func_str == ASINH) return std::asinh(radian_value);
	if (math_func_str == ACOSH) return std::asinh(radian_value);
	if (math_func_str == ATANH) return std::atanh(radian_value);
	if (math_func_str == ARCTANH) return 1.0 / std::atanh(radian_value);
	return -1.0;
}

void MathExpressionParser::calculate_in_math_functions(std::stack<std::stack<long double>>&current_math_function_calculate_stack, std::stack<std::string>&math_functions_stack, const char* token)
{
	double math_result(0);
	bool parametr(false);
	if (current_math_function_calculate_stack.size() > 1) parametr = true;
	if (current_math_function_calculate_stack.top().size() > 1 || (token[0]==FACTORIAL || token[0]==PERCENT)) calculation_inside_stack(current_math_function_calculate_stack.top(), token);
	else
	{
		try
		{
			math_result = current_math_function_calculate_stack.top().top();
			current_math_function_calculate_stack.top().pop();
			if (parametr) current_math_function_calculate_stack.pop();
			current_math_function_calculate_stack.top().push(math_function(math_functions_stack.top(), math_result));
			math_functions_stack.pop();
		}
		catch (const NegativeValueInLogarithmicFunctionException&)
		{
			throw;
		}
		catch (const NegativeValueInSquareRootFunctionException&)
		{
			throw;
		}
	}
}

