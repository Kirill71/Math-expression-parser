#ifndef DIVISION_BY_ZERO_EXCEPTION_H
#define DIVISION_BY_ZERO_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class DivedeByZeroException: public runtime_error
{
public:
	DivedeByZeroException() :runtime_error("attempted to divide by zero") {};
};
#endif // !DIVISION_BY_ZERO_EXCEPTION_H