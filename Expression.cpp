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
	size_t size = infix_expression.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (infix_expression[i]=='ѕ'||isdigit(infix_expression[i]) || (infix_expression[i] == POINT) ||
			(infix_expression[i] == COMA) ||
			(infix_expression[i] >= ALPHABET_BEGIN && infix_expression[i] <= ALPHABET_END))
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
			if (stack.empty()) stack.push(infix_expression[i]);	// ≈сли стек пуст то сразу кладу в него символ так как это ветвь else - то € уверен, что это знак оператора.
			else										// рассматрива вариант - если стек не пуст.
			{
				if (infix_expression[i] == RIGHT_BRACKET)	//  ѕроверка скобок.
				{
					while (stack.top() != LEFT_BRACKET)
					{
						from_stack_to_out_str(postfix_expression, stack);
						if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
					}
					stack.pop();
				}
				else									// если это не скобка - значит это оператор, тогда провер€ю его приоритетность и добавл€ю после этого в стек.
				{
					if (priority(infix_expression[i]) <= priority(stack.top()) && (infix_expression[i] != LEFT_BRACKET))// провер€ю не €вл€юетс€ ли входной символ левой скобкой, что бы не портила приоритетность
					{
						from_stack_to_out_str(postfix_expression, stack);
						if (postfix_expression.back() != SPACE) postfix_expression.push_back(SPACE);
					}
					stack.push(infix_expression[i]);
				}
			}
		}
	}
	while (!stack.empty()) //поюзать empty // выталкиваю элементы из стека в выходную строку
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

void  Expression::from_stack_to_out_str(string& _postfix_expression, stack<char>& stack)
{
	_postfix_expression.push_back(stack.top());
	stack.pop();
}