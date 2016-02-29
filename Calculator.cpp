#include"Calculator.h"

Calculator::Calculator(const string& _exp) :calc_expression(_exp), result() {}

Calculator::~Calculator()
{
	calc_expression.~Expression();
}

const string& Calculator::calculate()
{
	double numeric_result;
	try
	{
		ExpressionErrorController::check_all_errors(calc_expression.get_infix_expression());
		calc_expression.convert_from_infix_to_postfix_notation();
	}
	catch (UnmatchedBracketsException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (UnknownSintaxException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (UnknownOperatorException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	catch (DivedeByZeroException &ex)
	{
		return ExpressionErrorController::exception_handling(ex, result);
	}
	numeric_result= this->calculate_postfix_expression();
	return result_front_view(numeric_result, result);
}

const string & Calculator::result_front_view(double numeric_result, string & front_view)
{
	if ((numeric_result - int(numeric_result)) == 0.0)
	{
		front_view = move(to_string(static_cast<int>(numeric_result)));
		return optimaze_front_view_result(result);
	}
	else
	{
		front_view = move(to_string(static_cast<float>(numeric_result)));
		return optimaze_front_view_result(result);
	}
}

const string & Calculator::optimaze_front_view_result( string & front_view)
{
	front_view.shrink_to_fit();
	return front_view;
}

double Calculator::calculate_postfix_expression()
{
	size_t i(0);
	string string_to_number;
	stack<double> stack;
	double current_const(0);
	size_t size = calc_expression.get_postfix_expression().size();
	string postfix_notation(calc_expression.get_postfix_expression());
	while (i < size)
	{
		switch (postfix_notation[i])
		{
		case e: {stack.push(M_E); i += 2; break;}
		case Ï: {stack.push(M_PI); i += 2; break; }
		} 
			if (isdigit(postfix_notation[i])
				|| (postfix_notation[i] == DEDACTION && isdigit(postfix_notation[i + 1]) && i < size - 1))
				from_string_to_stack(string_to_number, postfix_notation, stack, i);
			else
				calculation_inside_stack(stack, postfix_notation, i);
	}
	return stack.top();
}

void  Calculator::digit_return(string& value, const string& postfix_notation, size_t& pos)
{
	value.clear();
	while (postfix_notation[pos] != SPACE)
	{
		value.push_back(postfix_notation[pos]);
		++pos;
	}
	++pos;
}

void Calculator::from_string_to_stack(string& string_to_number, string& postfix_notation, stack<double>& stack, size_t& pos)
{
	digit_return(string_to_number, postfix_notation, pos);
	stack.push(stof(string_to_number));
}

void Calculator::calculation_inside_stack(stack<double>& stack, const string& postfix_notation, size_t& pos)
{
	double op1, op2;
	switch (postfix_notation[pos])
	{
	case ADDITION: { operation(op1, op2, stack, pos); stack.push(op1 + op2); break; }
	case DEDACTION: { operation(op1, op2, stack, pos); stack.push(op1 - op2); break; }
	case MULTIPLE: { operation(op1, op2, stack, pos); stack.push(op1 * op2); break; }
	case DIVISION: { operation(op1, op2, stack, pos);  if (op2 == 0.0)throw DivedeByZeroException(); else stack.push(op1 / op2); break; }
	case POWER: {operation(op1, op2, stack, pos); stack.push(pow(op1, op2)); break; }
	default:
		return;
	}
}

void  Calculator::operation(double& op1, double& op2, stack<double>& stack, size_t& index)
{
	op2 = stack.top();
	stack.pop();
	op1 = stack.top();
	stack.pop();
	index += 2;
}