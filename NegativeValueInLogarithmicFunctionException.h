#ifndef NEGATIVE_VALUE_IN_LOGARIYHMIC_FUNCTION_EXCEPTION_H
#define NEGATIVE_VALUE_IN_LOGARIYHMIC_FUNCTION_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class NegativeValueInLogarithmicFunctionException : public runtime_error
{
public:
	NegativeValueInLogarithmicFunctionException() :runtime_error("Negative value in logarithmic function.") {};
};

#endif // !NEGATIVE_VALUE_IN_LOGARIYHMIC_FUNCTION_EXCEPTION_H

