#include "ExpressionErrorController.h"

bool ExpressionErrorController::is_known_operator(const char functor)
{
	return (is_math_operator(functor) || is_operator(functor));
}

bool ExpressionErrorController::is_math_operator(const char op)
{
	switch (op)
	{
	case ADDITION: case DEDACTION:
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
	case e: case Ï: case FACTORIAL: case PERSENT:
		return true;
	default:
		return false;
	}
}

bool ExpressionErrorController::is_math_operator_or_fuctorial_op_persent(const char simbol)
{
	if (is_math_operator(simbol)) return true;
	return  (simbol == FACTORIAL || simbol == PERSENT);
}

const string & ExpressionErrorController::exception_handling(const runtime_error& ex, string& str)
{
	
	str = ex.what();
	str.shrink_to_fit();
	return str;
}

void ExpressionErrorController::check_all_errors(const string & str)
{
	size_t size= str.size();
	stack<char> stack;
	
	if (is_math_operator(str[size - 1])) throw UnknownSintaxException();
	for (size_t i(0); i < size; ++i)
	{
		if (is_math_operator(str[i]) && is_math_operator(str[i + 1])&&i<size-1) throw UnknownSintaxException();
		if (!is_known_operator(str[i]) && !isdigit(str[i]) && !is_alpha(str[i])) throw  UnknownOperatorException();
		if (str[i] == LEFT_BRACKET) stack.push(str[i]);
		else
			if (str[i] == RIGHT_BRACKET)
			{
				(!stack.empty()) ? stack.pop() : stack.push(str[i]);
			}
	}
	if (!stack.empty()) throw UnmatchedBracketsException();
}