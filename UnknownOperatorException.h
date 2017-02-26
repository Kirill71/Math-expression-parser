#ifndef UNKNOWN_OPERATOR_EXCEPTION_H
#define UNKNOWN_OPERATOR_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class UnknownOperatorException : public runtime_error
{
public:
	UnknownOperatorException() :runtime_error("Unknown operator.") {};
};
#endif // !UNKNOWN_OPERATOR_EXCEPTION_H