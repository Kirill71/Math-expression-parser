#include "ExpressionErrorController.h"

#include "Definition.h"
#include "MathExpressionException.h"

#include <stack>

bool ExpressionErrorController::is_known_operator(const char functor)
{
	return is_math_operator(functor) || is_operator(functor);
}

bool ExpressionErrorController::is_math_operator(const char op)
{
	switch (op)
	{
	case ADDITION: case DEDUCTION:
	case MULTIPLE: case DIVISION: case POWER:
		return true;
	default:
		return false;
	}
}

bool ExpressionErrorController::is_operator(const char functor)
{
	switch (functor)
	{
	case POWER: case POINT:case COMA:
	case LEFT_BRACKET:case RIGHT_BRACKET:
	case LEFT_FUNCTION_BRACKET: case RIGHT_FUNCTION_BRACKET:
	case SPACE:case ALPHABET_BEGIN: case ALPHABET_END:
	case e_num: case p_num: case FACTORIAL: case PERCENT:
		return true;
	default:
		return false;
	}
}

bool ExpressionErrorController::is_math_operator_or_factorial_or_percent(const char symbol)
{
	if (is_math_operator(symbol)) return true;
	return symbol == FACTORIAL || symbol == PERCENT;
}

const std::string & ExpressionErrorController::exception_handling(const std::runtime_error& ex, std::string& str)
{
	str = ex.what();
	str.shrink_to_fit();
	return str;
}

void ExpressionErrorController::check_all_errors(const std::string & expression)
{
	const size_t n = expression.size();
	std::stack<char> stack;
	
	if (is_math_operator(expression[n - 1])) {
		throw UnknownSyntaxException();
	}
	for (size_t i = 0; i < n; ++i)
	{
		if (is_math_operator(expression[i]) && is_math_operator(expression[i + 1]) && i< n - 1) throw UnknownSyntaxException();
		if (!is_known_operator(expression[i]) && !isdigit(expression[i]) && !is_alpha(expression[i])) throw  UnknownOperatorException();
		if (expression[i] == LEFT_BRACKET) stack.push(expression[i]);
		else
			if (expression[i] == RIGHT_BRACKET)
			{
				(!stack.empty()) ? stack.pop() : stack.push(expression[i]);
			}
	}

	if (!stack.empty())
	{
		throw UnmatchedBracketsException();
	}
}