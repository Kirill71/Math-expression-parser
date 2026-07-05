#include "MathExpressionParser.h"

#include <gtest/gtest.h>

struct MathExpressionParams {
    std::string expression;
    std::string result;
};
class MathExpression: public ::testing::TestWithParam<MathExpressionParams> {
protected:
    MathExpressionParser calculator;
};

TEST_P(MathExpression, SimpleExpressionCheck) {
    auto [expression, result] = GetParam();
    EXPECT_EQ(result, calculator.eval(expression));
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
                        MathExpressionParams{"-1*(3+5)", "-8"},
                        MathExpressionParams{"-(3+5)", "-8"}));

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
                        MathExpressionParams{"actg(45)", "1.502012"},
                        MathExpressionParams{"100+20%", "120"},
                        MathExpressionParams{"-5!", "-120"}));


INSTANTIATE_TEST_SUITE_P(NegationOfParenthesizedExpressions, MathExpression,
                        ::testing::Values(MathExpressionParams{"-(3)", "-3"},
                        MathExpressionParams{"-(2*3)", "-6"},
                        MathExpressionParams{"-(10/2)", "-5"},
                        MathExpressionParams{"-(2+3)*2", "-10"},
                        MathExpressionParams{"-(3+4*2)", "-11"},
                        MathExpressionParams{"-sqrt(16)", "-4"}));


INSTANTIATE_TEST_SUITE_P(OperatorPrecedenceAndAssociativity, MathExpression,
                        ::testing::Values(MathExpressionParams{"2*3^2", "18"},
                        MathExpressionParams{"2^3^2", "64"},
                        MathExpressionParams{"10/2*5", "25"},
                        MathExpressionParams{"10-2-3", "5"},
                        MathExpressionParams{"100/10/2", "5"},
                        MathExpressionParams{"2^(3-1)", "4"},
                        MathExpressionParams{"(-2)^2", "4"}));


INSTANTIATE_TEST_SUITE_P(NestedBracketsAndFunctions, MathExpression,
                        ::testing::Values(MathExpressionParams{"((2+3))", "5"},
                        MathExpressionParams{"(2+3)*(4-1)/(5-2)", "5"},
                        MathExpressionParams{"sqrt(sqrt(16))", "2"},
                        MathExpressionParams{"sqrt(16)+3", "7"},
                        MathExpressionParams{"sqrt(4)*sqrt(9)", "6"},
                        MathExpressionParams{"sin(30)+cos(60)", "1"},
                        MathExpressionParams{"abs(-5)+abs(5)", "10"},
                        MathExpressionParams{"2*(3+4!)", "54"}));


INSTANTIATE_TEST_SUITE_P(PercentAndFactorialEdgeCases, MathExpression,
                        ::testing::Values(MathExpressionParams{"3!!", "720"},
                        MathExpressionParams{"0!", "1"},
                        MathExpressionParams{"3+4!", "27"},
                        MathExpressionParams{"100-20%", "80"},
                        MathExpressionParams{"50-10%", "45"},
                        MathExpressionParams{"5%+5", "5.050000"}));


INSTANTIATE_TEST_SUITE_P(ExceptionsWithComplexExpressions, MathExpression,
                        ::testing::Values(MathExpressionParams{"(2+3))", "Unmatched brackets."},
                        MathExpressionParams{"sqrt(16", "Unmatched brackets."},
                        MathExpressionParams{"2/(3-3)", "Division by zero."},
                        MathExpressionParams{"sqrt(16)+", "Unknown syntax."}));


