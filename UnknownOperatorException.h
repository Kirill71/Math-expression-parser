#ifndef UNKNOWN_OPERATOR_EXCEPTION
#define UNKNOWN_OPERATOR_EXCEPTION

#include<stdexcept>

using std::runtime_error;

class UnknownOperatorException : public runtime_error
{
public:
	UnknownOperatorException() :runtime_error("unknown operator") {};
};
#endif // !UNKNOWN_OPERATOR_EXCEPTION