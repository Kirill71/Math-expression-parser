
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<cctype>
#include<conio.h>
#include<memory>
#include"Expression.h"
#include"ExpressionErrorController.h"
#include"DivideByZeroException.h"
#include"NegativeValueInLogarithmicFunctionException.h"
#include"NegativeValueInSquareRootFunctionException.h"

using std::stof;
using std::to_string;
using std::pair;


/*_declspec(dllexport)*/ class Calculator
{
public:
	explicit Calculator(const string&);
	~Calculator();
	/*_declspec(dllexport)*/ const string& calculate();
private:
	void factorial(double,stack<long double>&);
	const string& result_front_view(double, string&);
	const string& optimaze_front_view_result(string&);
	double calculate_postfix_expression(); // вычисление постфиксной нотации
	void calculation_inside_stack(stack<long double>&, const char*); //вычисления текущей операции на стеке
	void operation(double&, double&, stack<long double>&);// извлечение операндов из стека перед вычислением
	void operation(double&, stack<long double>&);
	bool is_constant(char,stack<long double>&);// является ли константой данный символ( констант две: число Ейлера и число Пи);
	double math_function(const string&,double); // вычисление результата математичесской функции
	void calculate_in_math_functions(stack<stack<long double>>&, stack<string>&,const char*); // вычисление математического выражения (является частью метода calculate_postfix_expression)
	std::unique_ptr<Expression> calc_expression; 
	string result;
};

#endif // !CALCULATOR_H