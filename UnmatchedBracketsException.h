#ifndef UNMATCHED_BRACKETS_EXCEPTION_H
#define UNMATCHED_BRACKETS_EXCEPTION_H

#include<stdexcept>

using std::runtime_error;

class UnmatchedBracketsException : public runtime_error
{
public:
	UnmatchedBracketsException() :runtime_error("Unmatched brackets.") {};
};
#endif // !UNMATCHED_BRACKETS_EXCEPTION_H