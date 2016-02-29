
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<Windows.h>
#include<cctype>
#include<conio.h>
#include"Expression.h"
#include"ExpressionErrorController.h"
#include"DivideByZeroException.h"

using std::stof;
using std::to_string;


/*_declspec(dllexport)*/ class Calculator
{
public:
	Calculator(const string&);
	~Calculator();
	/*_declspec(dllexport)*/ const string& calculate();
private:
	const string& result_front_view(double, string&);
	const string& optimaze_front_view_result(string&);
	double calculate_postfix_expression();
	void digit_return(string& value, const string& postfix_notation, size_t& pos);
	void from_string_to_stack(string&, string&, stack<double>&, size_t&);
	void calculation_inside_stack(stack<double>&, const string&, size_t&);
	void operation(double&, double&, stack<double>&, size_t&);
	Expression calc_expression;
	string result;
};

#endif // !CALCULATOR_H