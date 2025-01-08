#ifndef UNKNOWN_SINTAX_EXCEPTION_H
#define UNKNOWN_SINTAX_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class UnknownSyntaxException : public runtime_error
{
public:
	UnknownSyntaxException() : runtime_error("Unknown syntax.") {};
};
#endif // !UNKNOWN_SINTAX_EXCEPTION_H