
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<cctype>
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
	double calculate_postfix_expression(); // ���������� ����������� �������
	void calculation_inside_stack(stack<long double>&, const char*); //���������� ������� �������� �� �����
	void operation(double&, double&, stack<long double>&);// ���������� ��������� �� ����� ����� �����������
	void operation(double&, stack<long double>&);
	bool is_constant(char,stack<long double>&);// �������� �� ���������� ������ ������( �������� ���: ����� ������ � ����� ��);
	double math_function(const string&,double); // ���������� ���������� ��������������� �������
	void calculate_in_math_functions(stack<stack<long double>>&, stack<string>&,const char*); // ���������� ��������������� ��������� (�������� ������ ������ calculate_postfix_expression)
	std::unique_ptr<Expression> calc_expression; 
	string result;
};

#endif // !CALCULATOR_H