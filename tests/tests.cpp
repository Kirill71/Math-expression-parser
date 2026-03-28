#include "Calculator.h"

#include <gtest/gtest.h>

struct MathExpressionParams {
    std::string expression;
    std::string result;
};
class MathExpression: public ::testing::TestWithParam<MathExpressionParams> {
protected:
    Calculator calculator;
};

TEST_P(MathExpression, SimpleExpressionCheck) {
    auto [expression, result] = GetParam();
    EXPECT_EQ(result, calculator.calculate(expression));
}

INSTANTIATE_TEST_SUITE_P(SimpleOperations, MathExpression,
                        ::testing::Values(MathExpressionParams{"3+3", "6"},
                        MathExpressionParams{"3-3", "0"},
                        MathExpressionParams{"4*4", "16"},
                        MathExpressionParams{"3/3", "1"},
                        MathExpressionParams{"3 / 3", "1"},
                        MathExpressionParams{"3 + 3 - (5 + 2)", "-1"},
                        MathExpressionParams{"3+4*(5-7)", "-5"},
                        MathExpressionParams{"(3+4)*(5+7)", "84"}));


INSTANTIATE_TEST_SUITE_P(NegativeSimpleOperations, MathExpression,
                        ::testing::Values(MathExpressionParams{"-3+3", "0"},
                        MathExpressionParams{"-3-3", "-6"},
                        MathExpressionParams{"-4*(-4)", "16"},
                        MathExpressionParams{"-3/(-3)", "1"},
                        MathExpressionParams{"-3+3", "0"},
                        MathExpressionParams{"-4", "-4"},
                        MathExpressionParams{"-1*(3+5)", "-8"}
                        /*MathExpressionParams{"-(3+5)", "-8"}*/));

INSTANTIATE_TEST_SUITE_P(ExceptionsWithSimpleOperations, MathExpression,
                        ::testing::Values(MathExpressionParams{"-3-", "Unknown syntax."},
                        MathExpressionParams{"-4*-4", "Unknown syntax."},
                        MathExpressionParams{"-3/-3", "Unknown syntax."},
                        MathExpressionParams{"1/0", "Division by zero."},
                        MathExpressionParams{"sqrt(-5)", "Negative value in square root function."},
                        MathExpressionParams{"3+5)", "Unmatched brackets."},
                        MathExpressionParams{"(3+5)*{2-4}/[4-7]", "Unknown operator."},
                        MathExpressionParams{"2^-3", "Unknown syntax."},
                        MathExpressionParams{"ln(-5)", "Negative value in logarithmic function."},
                        MathExpressionParams{"lg(-5)", "Negative value in logarithmic function."},
                        MathExpressionParams{"logb(-5)", "Negative value in logarithmic function."}));


INSTANTIATE_TEST_SUITE_P(OperationsWithMathFunctions, MathExpression,
                        ::testing::Values(MathExpressionParams{"5!", "120"},
                        MathExpressionParams{"sqrt(25)", "5"},
                        MathExpressionParams{"sqrt(50)", "7.071068"},
                        MathExpressionParams{"2^3", "8"},
                        MathExpressionParams{"-2^3", "-8"},
                        MathExpressionParams{"2^(-3)", "0.125000"},
                        MathExpressionParams{"120%", "1.200000"},
                        MathExpressionParams{"logb(8)", "3"},
                        MathExpressionParams{"abs(-5)", "5"},
                        MathExpressionParams{"sin(90)", "1"},
                        MathExpressionParams{"cos(90)", "0"},
                        MathExpressionParams{"tg(45)", "1.000000"},
                        MathExpressionParams{"ctg(45)", "1"},
                        MathExpressionParams{"asin(45)", "0.903339"},
                        MathExpressionParams{"acos(45)", "0.667457"},
                        MathExpressionParams{"atg(45)", "0.665774"},
                        MathExpressionParams{"actg(45)", "1.502012"}
                        /*MathExpressionParams{"100+20%", "120"}*/
                        /*MathExpressionParams{"-5!", "-120"}*/));


