#include"Calculator.h"
using std::cin;
using std::cout;
using std::endl;

int main()
{
	string input_string;
	cout << "input calculation expression:" << endl;
	cin >> input_string;
	input_string.shrink_to_fit();
	Calculator obj1(input_string);
	cout<<obj1.calculate()<<endl;

	return 0;
}