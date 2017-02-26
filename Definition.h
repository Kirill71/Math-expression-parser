#ifndef DEFINITION
#define DEFINITION
#define _USE_MATH_DEFINES
#include<iostream>
#include<math.h>
#include<ctype.h>

using std::string;

#define  ERROR_FAILURE 17;
// строковые определения.
#define LEFT_BRACKET_C_STR "("
#define ADDITION_C_STR "+"
#define DEDACTION_C_STR "-"
#define MULTIPLE_C_STR "*"
#define DIVISION_C_STR "/"
#define RIGHT_BRACKET_C_STR ")"
#define POINT_C_STR "."
#define COMA_C_STR "," 
#define POWER_C_STR "^"
#define SPACE_C_STR " "
#define SPACE_C_STR " "
#define ALPHABET_BEGIN 'a'
#define ALPHABET_END 'z'
#define LEFT_FUNCTION_BRACKET_C_STR "["
#define RIGHT_FUNCTION_BRACKET_C_STR "]"
#define FACTORIAL_C_STR "!" //зарезервировано
#define PERSENT_C_STR "%"	//зарезервировано
//constants
#define	e_C_STR	"e"
#define	П_C_STR	"п"
#define LEFT_BRACKET '('
#define ADDITION '+'
#define DEDACTION '-'
#define MULTIPLE '*'
#define DIVISION '/'
#define RIGHT_BRACKET ')'
#define POINT '.'
#define COMA ',' 
#define POWER '^'
#define SPACE ' '
#define SPACE_C_STR " "
#define ALPHABET_BEGIN 'a'
#define ALPHABET_END 'z'
#define LEFT_FUNCTION_BRACKET '['
#define RIGHT_FUNCTION_BRACKET ']'
#define FACTORIAL '!' //зарезервировано
#define PERSENT '%'	//зарезервировано
//constants
#define	e	'e'
#define	П	'п'
//math_functions
#define SIN "sin"
#define COS "cos"
#define TAN  "tg"
#define CTAN "ctg"
#define SQRT "sqrt"
#define LN "ln"
#define LG "lg"
#define LOGB "logb"
#define ASIN "asin"
#define ACOS "acos"
#define ATAN "atg"
#define ACTAN "actg"
#define ABS   "abs"
#define SINH  "sinh"
#define COSH  "cosh"
#define TANH "tgh"
#define CTANH "ctgh"
#define ASINH "asinh"
#define ACOSH "acosh"
#define ATANH "atgh"
#define ACTANH "actgh"
#define MOD "mod" // зарезервировано

bool is_alpha(const char);
bool is_point(const char);
bool is_digit(const char);
bool is_digit(const char*);
bool is_digit_or_alpha(const string::const_iterator &);
bool is_operator(const string::const_iterator &);
bool is_bracket(const string::const_iterator &);
size_t group_number(const string::const_iterator &);
bool is_unary_minus(const string::const_iterator &);
size_t simbol_type(const string::const_iterator &);
#endif // !DEFINITION



