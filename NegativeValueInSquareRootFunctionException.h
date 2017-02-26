#ifndef NEGATIVE_VALUE_IN_SQUARE_ROOT_FUNCTION_EXCEPTION_H
#define NEGATIVE_VALUE_IN_SQUARE_ROOT_FUNCTION_EXCEPTION_H
#include<stdexcept>

using std::runtime_error;

class NegativeValueInSquareRootFunctionException : public runtime_error
{
public:
	NegativeValueInSquareRootFunctionException():runtime_error("Negative value in square root function.") {};
};

#endif // !NEGATIVE_VALUE_IN_SQUARE_ROOT_FUNCTION_EXCEPTION_H

