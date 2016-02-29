#ifndef UNKNOWN_SINTAX_EXCEPTION_H
#define UNKNOWN_SINTAX_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class UnknownSintaxException : public runtime_error
{
public:
	UnknownSintaxException() : runtime_error("unknown sintax") {};
};
#endif // !UNKNOWN_SINTAX_EXCEPTION_H