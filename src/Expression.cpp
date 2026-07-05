#include "Expression.h"
#include "Definition.h"
#include <utility>

Expression::Expression(std::string _exp) : infix_expression(std::move(_exp))
{
	infix_expression.shrink_to_fit();
}

void Expression::convert_from_infix_to_postfix_notation()
{
	std::stack<char> stack;
	const size_t n = infix_expression.size();
	size_t opened_left_brackets(0);
	size_t current_math_function(0);

	stack.push(SPACE);

	for (size_t i(0); i < n; ++i)
	{
		if (infix_expression[i] == p_num || isdigit(infix_expression[i]) || is_point(infix_expression[i]) ||
			is_alpha(infix_expression[i]))
		{
			if (infix_expression[i] == COMA) postfix_expression.push_back(POINT);
			else
				postfix_expression.push_back(infix_expression[i]);
		}
		else
		{
			if (infix_expression[i] == DEDUCTION)
			{
				if (i == 0 || infix_expression[i - 1] == LEFT_BRACKET)
				{
					if (i + 1 < n && (infix_expression[i + 1] == LEFT_BRACKET || is_alpha(infix_expression[i + 1])))
					{
						postfix_expression.push_back('0');
					}
					else
					{
						postfix_expression.push_back(DEDUCTION); continue;
					}
				}
			}

			if (!postfix_expression.empty() && postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
			if (infix_expression[i] == LEFT_BRACKET)
			{
				if (i != 0 && is_alpha(infix_expression[i - 1]))
				{
					++current_math_function;
					postfix_expression.push_back(LEFT_FUNCTION_BRACKET);
					postfix_expression.push_back(SPACE);
				}
				++opened_left_brackets;
			}
			if (infix_expression[i] == RIGHT_BRACKET)
			{
				while (stack.top() != LEFT_BRACKET)
				{
					from_stack_to_out_str(postfix_expression, stack);
					if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
				}
				stack.pop();
				if (current_math_function != 0 && opened_left_brackets == 1 || (current_math_function >= 2 && opened_left_brackets >= 2)) { postfix_expression.push_back(RIGHT_FUNCTION_BRACKET); --opened_left_brackets; --current_math_function; }
				else --opened_left_brackets;
			}
			else
			{
				if (stack.top() != SPACE)
				{
					if (priority(infix_expression[i]) <= priority(stack.top()) && (infix_expression[i] != LEFT_BRACKET))
					{
						from_stack_to_out_str(postfix_expression, stack);
						if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
					}
				}
				stack.push(infix_expression[i]);
			}
		}
	}
	while (stack.size() > 1)
	{
		if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
		from_stack_to_out_str(postfix_expression, stack);
	}

	postfix_expression.shrink_to_fit();
}

size_t Expression::priority(const char operand) const
{
	switch (operand)
	{
	case LEFT_BRACKET:
	case RIGHT_BRACKET:
	{return 1;}

	case ADDITION:
	case DEDUCTION:
	{return 2;}

	case MULTIPLE:
	case DIVISION:
	{return 3;}

	case POWER:
	{ return 4;}

	case FACTORIAL:
	case PERCENT:
	{ return 5;}

	default: { return -1; }
	}
}

void Expression::from_stack_to_out_str(std::string& _postfix_expression, std::stack<char>& stack)
{
	_postfix_expression.push_back(stack.top());
	stack.pop();
}