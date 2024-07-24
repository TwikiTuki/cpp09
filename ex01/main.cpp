#include <iostream>
#include "RPN.hpp"

void test(std::string inp)
{
	float result = 0;
	calculator calc;
	std::cout << "Testing: >" << inp << "<" << std::endl;
	try
	{
		result = calc.calculate(std::string(inp));
		std::cout << "  KO ";
	} catch (std::exception& e)
	{
		std::cout << "  OK ";
	}
	std::cout << "Test(" << inp << "): ";
	std::cout << result << std::endl;
	std::cout << std::endl;

}

void test(std::string inp, float expected)
{
	float result;
	std::cout << "Testing: >" << inp << "<" << std::endl;
	calculator calc;
	result = calc.calculate(std::string(inp));
	if (result - expected > 0.001 || expected -result > 0.001)
		std::cout << "  KO ";
	else
		std::cout << "  OK ";
	std::cout << "Test(" << inp << "): ";
	std::cout << result << ", " << expected << std::endl;
	std::cout << std::endl;
}

void normalTests(void)
{
	test("45+", 9);
	test("45-", -1);
	test("45*", 20);
	test("93/", 3);
	test("34-", -1);
	test("34+", 7.0);
	test("52-", 3);
	test("23*", 6.0);
	test("82/", 4.0);
	test("123+*", 5.0);
	test("42/3*", 6.0);
	test("52+3-", 4.0);
	test("63*2/", 9.0);
	test("23+4*", 20.0);
	test("84/2*", 4.0);
	test("12+3-4*", 0.0);
	test("52*3/4+", 7.33333);
	test("63/2*5+", 9);
	test("23*4+5/", 2.0);
	test("84/2*6+", 10.0);
	test("12+3-4*5/", 0);
	test("52*3/4+6-", 1.33333);
	test("63/2*5+7-", 2);
	test("23*4+5/6-", -4);
	test("84/2*6+7-", 3);
}

void spacesTests()
{
	test("  6 3 * 2 /", 9.0);
	test(" 2 3 + 4 * ", 20.0);
	test("8 4 / 2 *", 4.0);
	test("12 +3 -4*", 0.0);
	test("52*3/4+  ", 7.33333);
	test("  63/2*5+", 9);
	test("23*  4+5/", 2.0);
}

void exceptionTests(void)
{
	test("");
	test("+45");
	test("m45+");
	test("45o+");
	test("45%+");
	test("45+%");
	test("457+");
	test("4+");
}

int main(int argc, char **argv)
{
	//normalTests();
	//exceptionTests();
	//spacesTests();
	return(0);
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return (1);	
	}
	calculator calc;
	try
	{
		std::cout << calc.calculate(argv[1]) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error" << std::endl;
		return (1);	
	}
}
