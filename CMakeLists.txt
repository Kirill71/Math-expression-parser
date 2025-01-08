cmake_minimum_required(VERSION 3.28)
project(MathExpressionParser)

set(CMAKE_CXX_STANDARD 20)

set(SRC
    Calculator.cpp
        Expression.cpp
    ExpressionErrorController.cpp
    main.cpp
)

set(HEAD
    Calculator.h
    Definition.h
    Expression.h
    ExpressionErrorController.h
    DivideByZeroException.h
    NegativeValueInLogarithmicFunctionException.h
    NegativeValueInSquareRootFunctionException.h
    UnknownOperatorException.h
    UnknownSyntaxException.h
    UnmatchedBracketsException.h
        Definition.cpp
)
add_executable(${PROJECT_NAME} ${HEAD} ${SRC})