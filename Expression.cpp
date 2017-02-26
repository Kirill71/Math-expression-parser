#include"Expression.h"

Expression::Expression(const string& _exp) :infix_expression(move(_exp)), postfix_expression()
{
	infix_expression.shrink_to_fit();
}

Expression::~Expression()
{
	infix_expression.~basic_string();
	postfix_expression.~basic_string();
}

void Expression::convert_from_infix_to_postfix_notation()
{
	stack<char> stack;
	size_t size(infix_expression.size());
	bool is_math_function(false);
	size_t opened_left_brackets(0);
	size_t current_math_function(0);

	/*char* buffer;
	const char* token = strtok_s(const_cast<char*>(infix_expression.c_str()), SPACE_C_STR, &buffer);
	string str;*/
	stack.push(SPACE);

	/*while (token != nullptr)
	{
		str = token;
			if (token[0] == ѕ || isalnum(token[0])) postfix_expression.push_back+=str; postfix_expression.push_back(SPACE);


	}*/
	for (size_t i(0); i < size; ++i)
	{
		if (infix_expression[i] == ѕ || isdigit(infix_expression[i]) || is_point(infix_expression[i]) ||
			is_alpha(infix_expression[i]))
		{
			if (infix_expression[i] == COMA) postfix_expression.push_back(POINT); // провер€ю какой разделитель используетс€. ≈сли ',' - мен€ю на '.'.(ќсталось с консольной версии. ¬еро€тно в gui версии не пригодитс€.)
			else
				postfix_expression.push_back(infix_expression[i]); // если число сразу добавл€ю его в выходную строку - postfix_expression.
		}
		else
		{
			if (infix_expression[i] == DEDACTION)
			{
				if (i == 0 || infix_expression[i - 1] == LEFT_BRACKET)
				{
					postfix_expression.push_back(DEDACTION); continue;
				}
			}

			if (postfix_expression.size() > 0 && postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE); // между символами выходной строки ставлю по одному пробелу - что бы было удобнее парсить.
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
			if (infix_expression[i] == RIGHT_BRACKET)	//  ѕроверка скобок.
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
			else									// если это не скобка - значит это оператор, тогда провер€ю его приоритетность и добавл€ю после этого в стек.
			{
				if (stack.top() != SPACE)
				{
					if (priority(infix_expression[i]) <= priority(stack.top()) && (infix_expression[i] != LEFT_BRACKET))// провер€ю не €вл€юетс€ ли входной символ левой скобкой, что бы не портила приоритетность
					{
						from_stack_to_out_str(postfix_expression, stack);
						if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
					}
				}
				stack.push(infix_expression[i]);
			}
		}
	}
	while (stack.size() > 1) //поюзать empty // выталкиваю элементы из стека в выходную строку
	{
		if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
		from_stack_to_out_str(postfix_expression, stack);
	}

	postfix_expression.shrink_to_fit();
}

size_t Expression::priority(char functor) const
{
	switch (functor)
	{
	case LEFT_BRACKET:
	case RIGHT_BRACKET:
	{return 1; break; };

	case ADDITION:
	case DEDACTION:
	{return 2; break; };

	case MULTIPLE:
	case DIVISION:
	{return 3; break; };

	case POWER:
	{ return 4; break; }

	default: {return -1; }
	}
}

void Expression::with_space(const string & exp, string & infix_expression)
{
	size_t simbol = group_number(exp.begin()), current_simbol(0);
	infix_expression.push_back(*exp.begin());
	string::const_iterator pos;
	for (pos = next(exp.begin()); pos != exp.end(); ++pos)
	{
		current_simbol = simbol_type(pos);
		(simbol == current_simbol && (simbol != 3 || current_simbol != 3)) ? infix_expression.push_back(*pos) : infix_expression.push_back(SPACE); infix_expression.push_back(*pos);
		simbol = current_simbol;
	}
}
void  Expression::from_stack_to_out_str(string& _postfix_expression, stack<char>& stack)
{
	_postfix_expression.push_back(stack.top());
	stack.pop();
}