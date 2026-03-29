#include "src/MathExpressionParser.h"
#include <iostream>

int main()
{
	const auto validate = [](const std::string& input_string) {
		std::string refined_string;
		refined_string.reserve(input_string.length());
		for (const auto &c : input_string) {
			if (std::isspace(c)) {
				continue;
			}
			refined_string += c;
		}
		return refined_string;
	};

	std::string input_string;
	std::cout << "input calculation expression:" << std::endl;
	std::getline(std::cin, input_string);
	input_string.shrink_to_fit();

	MathExpressionParser parser{};
	std::cout<<parser.eval(validate(input_string))<< std::endl;

	return 0;
}