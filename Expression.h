#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<iostream>
#include<string>
#include<stack>
#include"Definition.h"

using std::stack;
using std::move;
using std::string;

class Expression
{
public:
	Expression(const string&);
	~Expression();
	void convert_from_infix_to_postfix_notation();// преобразует выражение в инфиксной нотации в постфиксную.
	inline const string& get_infix_expression()  const; //геттер для доступа к выражению в инфикстной нотации.
	inline 
		const string&  get_postfix_expression()const;  //геттер для доступа к выражению в постфиксной нотации.
private:
	size_t priority(char) const; // функция возвращает приоритет операции.
	void from_stack_to_out_str(string&, stack<char>&); // вспомогательная функция которая добавляет элементы из стека в выходную строку. Создана ради избежания дублирования кода.
	string infix_expression;
	string postfix_expression;
	
};

inline const string & Expression::get_infix_expression() const
{
	return infix_expression;
}

inline const string&  Expression::get_postfix_expression() const
{
	return postfix_expression;
}

#endif // !EXPRESSION_H