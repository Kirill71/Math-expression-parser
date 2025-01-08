#include"Calculator.h"
#include <cstring>

Calculator::Calculator(const string& _exp) :calc_expression(std::make_unique<Expression>(_exp)), result() {}

Calculator::~Calculator()
{
	calc_expression->~Expression();
}

const string& Calculator::calculate()
{
	double numeric_result;
	try
	{
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
	catch (const DivedeByZeroException &ex)
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

void Calculator::factorial(double op2, stack<long double>& stack)
{
	long long result(1);
	for (size_t i(1); i <=op2; ++i)
		result *= i;
	stack.push(result);
}

const string & Calculator::result_front_view(double numeric_result, string & front_view)
{
	if ((numeric_result - int(numeric_result)) == 0.0)
	{
		front_view = std::move(to_string(static_cast<int>(numeric_result)));
		return optimaze_front_view_result(result);
	}
	else
	{
		front_view = std::move(to_string(static_cast<float>(numeric_result)));
		return optimaze_front_view_result(result);
	}
}

const string & Calculator::optimaze_front_view_result(string & front_view)
{
	front_view.shrink_to_fit();
	return front_view;
}

double Calculator::calculate_postfix_expression()
{
	bool is_only_ariphmetic_expression(true);
	stack<string> math_functions_stack;
	stack<stack< long double>> current_math_function_calculate_stack;
	stack<long double> stack;
	const char* token=std::strtok(const_cast<char*>(calc_expression->get_postfix_expression().c_str()),SPACE_C_STR);
	while (token != nullptr) //���� ���� �������
	{
		if (is_alpha(token[0]) && token[0] != e) {math_functions_stack.push(token);current_math_function_calculate_stack.push(stack);}
		else
		{
			if (is_only_ariphmetic_expression) { current_math_function_calculate_stack.push(stack); is_only_ariphmetic_expression = false; }
		}
		is_constant(token[0], current_math_function_calculate_stack.top());
		if (is_digit(token))  current_math_function_calculate_stack.top().push(stof(token));
		else
		{			
			if (token[0] == RIGHT_FUNCTION_BRACKET) 
			{  
				calculate_in_math_functions(current_math_function_calculate_stack, math_functions_stack, token);
			}
			else
			{ 
				if ( ExpressionErrorController::is_math_operator_or_fuctorial_op_persent(token[0])) calculate_in_math_functions(current_math_function_calculate_stack, math_functions_stack, token);
			}
		}
		token = std::strtok(nullptr, SPACE_C_STR);
	}
	return current_math_function_calculate_stack.top().top();
}

void Calculator::calculation_inside_stack(stack<long double>&stack, const char *token)
{
	double op1(0), op2(0);
	if (token[0] == FACTORIAL || token[0] == PERSENT) operation(op2, stack);
	else	operation(op1, op2, stack);
	switch (token[0])
	{
	case ADDITION: { stack.push(op1 + op2); break;}
	case DEDACTION: {stack.push(op1 - op2); break;}
	case MULTIPLE: { stack.push(op1 * op2); break;}
	case DIVISION: {if (op2 == 0.0)throw DivedeByZeroException(); else stack.push(op1 / op2); break; }
	case POWER: {stack.push(pow(op1, op2)); break;}
	case FACTORIAL: {factorial(op2, stack); break;}
	case PERSENT: {  stack.push(op2 / 100.0); break; }
	default:
		return;
	}
}

void  Calculator::operation(double& op1, double& op2, stack<long double>& stack)
{
	operation(op2, stack);
	op1 = stack.top();
	stack.pop();
}

void Calculator::operation(double &op2, stack<long double>& stack)
{
	op2 = stack.top();
	stack.pop();
}

bool Calculator::is_constant(char simbol, stack< long double>&stack)
{
	if (simbol == e) {stack.push(M_E); return true;}
	if (simbol== p){stack.push(M_PI); return true;}
	return false;
}

double Calculator::math_function(const string & math_func_str, double value)
{
	if (math_func_str == SIN) return sin(value*M_PI / 180);
	if (math_func_str == COS) return cos(value*M_PI / 180);
	if (math_func_str == TAN) return tan(value*M_PI / 180);
	if (math_func_str == CTAN) return 1.0 / tan(value*M_PI / 180);
	if (math_func_str == SQRT) { if (value < 0.0) throw NegativeValueInSquareRootFunctionException(); else return sqrt(value);}
	if (math_func_str == LN) { if (value < 0.0)  throw NegativeValueInLogarithmicFunctionException(); else return log(value);}
	if (math_func_str == LG) { if (value < 0.0)  throw NegativeValueInLogarithmicFunctionException(); else return log10(value);}
	if (math_func_str == LOGB) { if (value < 0.0)  throw NegativeValueInLogarithmicFunctionException(); else return log2(value); }
	if (math_func_str == ABS) return abs(value);
	if (math_func_str == ASIN) return asin(value*M_PI / 180);
	if (math_func_str == ACOS) return acos(value*M_PI / 180);
	if (math_func_str == ATAN) return atan(value*M_PI / 180);
	if (math_func_str == ACTAN) return 1.0 / atan(value*M_PI / 180);
	if (math_func_str == SINH) return sinh(value*M_PI / 180);
	if (math_func_str == COSH) return cosh(value*M_PI / 180);
	if (math_func_str == TANH) return tanh(value*M_PI / 180);
	if (math_func_str == CTANH) return 1.0/tanh(value*M_PI / 180);
	if (math_func_str == ASINH) return asinh(value*M_PI / 180);
	if (math_func_str == ACOSH) return asinh(value*M_PI / 180);
	if (math_func_str == ATANH) return atanh(value*M_PI / 180);
	if (math_func_str == ACTANH) return 1.0 / atanh(value*M_PI / 180);
	return -1.0;
}

void Calculator::calculate_in_math_functions(stack<stack<long double>>&current_math_function_calculate_stack, stack<string>&math_functions_stack, const char* token)
{
	double math_result(0);
	bool parametr(false);
	if (current_math_function_calculate_stack.size() > 1) parametr = true;
	if (current_math_function_calculate_stack.top().size() > 1||(token[0]==FACTORIAL||token[0]==PERSENT)) calculation_inside_stack(current_math_function_calculate_stack.top(), token);
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

