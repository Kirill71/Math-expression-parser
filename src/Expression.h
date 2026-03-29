#pragma once
#include<string>
#include<stack>


class Expression
{
public:
	explicit Expression(std::string);

	void convert_from_infix_to_postfix_notation();
	const std::string& get_infix_expression() const;
	const std::string& get_postfix_expression() const;
private:
	size_t priority(char) const;
	void from_stack_to_out_str(std::string&, std::stack<char>&);
	std::string infix_expression;
	std::string postfix_expression{};
};

inline const std::string & Expression::get_infix_expression() const
{
	return infix_expression;
}

inline const std::string& Expression::get_postfix_expression()const
{
	return postfix_expression;
}
