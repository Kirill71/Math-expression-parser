#pragma once

#include<stdexcept>

class DivideByZeroException: public std::runtime_error
{
public:
    DivideByZeroException() : std::runtime_error("Division by zero.") {}
};

class NegativeValueInSquareRootFunctionException : public std::runtime_error
{
public:
    NegativeValueInSquareRootFunctionException(): std::runtime_error("Negative value in square root function.") {}
};

class NegativeValueInLogarithmicFunctionException : public std::runtime_error
{
public:
    NegativeValueInLogarithmicFunctionException() : std::runtime_error("Negative value in logarithmic function.") {}
};

class UnknownSyntaxException : public std::runtime_error
{
public:
    UnknownSyntaxException() : std::runtime_error("Unknown syntax.") {}
};

class UnmatchedBracketsException : public std::runtime_error
{
public:
    UnmatchedBracketsException() : std::runtime_error("Unmatched brackets.") {}
};

class UnknownOperatorException : public std::runtime_error
{
public:
    UnknownOperatorException() : std::runtime_error("Unknown operator.") {}
};