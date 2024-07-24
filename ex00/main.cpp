# include <iostream>
# include "BitcoinExchange.hpp"

#define OK GREEN << "OK " << RESET
#define KO RED << "KO " << RESET

void test_strDateToDays(std::string inpString, unsigned int expected)
{
	unsigned int	days;
	days = BitcoinExchange::dateStrToDays(inpString);
	std::cout << "Testing:  " << inpString << std::endl;
	if (days == expected)
	{
		std::cout << OK;
	}
	else
		std::cout << KO;
	std::cout << "res: " << days << ", expect: " << expected << std::endl;
}

//void tests_strDateToDays(void)
//{
//#include "tests.cpp"
//
//}

void test_parseDate(std::string strDate)
{
	t_date date;

	std::cout << "test: " << strDate << std::endl;
	date = BitcoinExchange::parseDate(strDate);
	std::cout << "res:  " << date.year 
			  << "-" << date.month
			  << "-" << date.day
			  << std::endl;
	std::cout << std::endl;
}

void tests_parseDate(void)
{
	test_parseDate("1996-03-23");
	test_parseDate("0-03-23");
	test_parseDate("1996-0-23");
	test_parseDate("1996-3-0");
	std::cout << "- - - - - - - - - -" << std::endl; 

	test_parseDate("199d6-03-23");
	test_parseDate("0-03-2+3");
	test_parseDate("1996-*0-23");
	test_parseDate("1996q-3-0");
	std::cout << "- - - - - - - - - -" << std::endl; 

	test_parseDate("");
	test_parseDate("-");
	test_parseDate("--");
	test_parseDate("---");
	std::cout << "- - - - - - - - - -" << std::endl; 

	test_parseDate("679");
	test_parseDate("38-3");
	test_parseDate("467-12-8");
	test_parseDate("234-3-29-489");
	test_parseDate("467--8");
	test_parseDate("467-8-");
	test_parseDate("-8-3");
}

void test_getPrice(BitcoinExchange& exchanger, std::string date, float expectedPrice)
{
	float price = exchanger.getPrice(date);

	if (price - expectedPrice > 0.0001 || expectedPrice - price > 0.0001)
		std::cout << KO ;
	else
		std::cout << OK ;
	std::cout << " Date: " << date << " Result: " << price << " Expected: " << expectedPrice << std::endl;
}

void tests_getPrice(void)
{
	BitcoinExchange exchanger;

	exchanger.loadPrices("data.csv");
	test_getPrice(exchanger, "2011-01-03", 0.3);
	test_getPrice(exchanger, "2011-01-09", 0.32);
	test_getPrice(exchanger, "2011-03-02", 0.95);
	test_getPrice(exchanger, "2011-07-19", 13.93);
	test_getPrice(exchanger, "2012-01-20", 6.57);
	test_getPrice(exchanger, "2012-01-21", 6.57);
	test_getPrice(exchanger, "2012-01-22", 6.57);
	test_getPrice(exchanger, "2012-01-23", 6.47);
	test_getPrice(exchanger, "2012-02-28", 4.98);
	test_getPrice(exchanger, "2012-02-29", 4.98);
	test_getPrice(exchanger, "2012-05-26", 5.15);

	test_getPrice(exchanger, "2011-01-03", 0.3);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	BitcoinExchange exchanger;
	std::cout << "Loading values" << std::endl;
	exchanger.loadPrices("data.csv");
	std::cout << "Printing history: " << argv[1] << std::endl;
	std::cout << std::endl;
	exchanger.printHistoryValues(argv[1]);
	//tests_getPrice();
	//exchanger.printHistoryValues("input.txt");
	//exchanger.printHistoryValues("invalidInp.txt");
	//exchanger.printHistoryValues("inpInvalidAmmounts.txt");
}
