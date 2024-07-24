#include "BitcoinExchange.hpp"
#include <iostream>
#include <utility>
#include <stdexcept>
#include <string>
#include <fstream>
#include <cstdlib>
const	std::map<day_count, day_count> BitcoinExchange::DAYS_IN_A_MONTH = BitcoinExchange::INITIALIZE_DAYS_IN_A_MONTH();

std::map<day_count, day_count> BitcoinExchange::INITIALIZE_DAYS_IN_A_MONTH()
{
	std::map<day_count, day_count> mp;
	mp[1] = 31;
	mp[2] = 28;
	mp[3] = 31;
	mp[4] = 30;
	mp[5] = 31;
	mp[6] = 30;
	mp[7] = 31;
	mp[8] = 31;
	mp[9] = 30;
	mp[10] = 31;
	mp[11] = 30;
	mp[12] = 31;
	return mp;
}

void ifstreamSkeepUntil(std::ifstream& stream, char end)
{
	while(stream.good() && stream.peek() != end) 
	{
		stream.get();
	}
	if (stream.peek() == end)
		stream.get();
}

void cleanBlank(std::string& inpStr)
{
	while(inpStr.size() > 0 && inpStr[0] == ' ')
	{
		inpStr.erase(0, 1);
	}
	while(inpStr.size() > 0 && inpStr[inpStr.size()-1] == ' ')
		inpStr.erase(inpStr.size()-1, 1);
}

bool checkFloatStr(const std::string& floatStr)
{
	std::string::const_iterator c = floatStr.begin(), end = floatStr.end();
	bool	decSep = false;
	bool 	numAfterDecSep = false;

	if (*c == '.')
		return (false);
	for (; c != end && *c; c++)
	{
		if (*c == '.' && !decSep)
			decSep = true;
		else if (*c < '0' || *c > '9')
		{
			return (false);
		}
		else if (decSep)
			numAfterDecSep = true;
	}
	if (decSep && !numAfterDecSep)
		return (false);
	return (true);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& orig)
{
	this->btcPrice = orig.btcPrice;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& orig)
{
	this->btcPrice = orig.btcPrice;
	return (*this);
}

bool BitcoinExchange::isLeap(day_count year)
{
	if ( year % 400 == 0)
		return (1);
	if (year % 100 == 0)
		return (0);
	return (year % 4 == 0);
}

day_count BitcoinExchange::monthToDays(day_count month)
{
	try
	{
		return BitcoinExchange::DAYS_IN_A_MONTH.at(month);
	}
	catch (std::out_of_range& exc)
	{
		return (0);
	}
}

day_count BitcoinExchange::monthAcumulatedDays(day_count month) // TODO Could acces its own array instead of adding all the months
{
	day_count acumulated = 0;
	for(day_count i = 1; i < month; i++)
	{
		acumulated +=  btce::monthToDays(i);
	}
	return(acumulated);
}

bool BitcoinExchange::loadPrices(std::string fileName)
{
	std::ifstream pricesStream(fileName.c_str());

	ifstreamSkeepUntil(pricesStream, '\n');
	while(pricesStream.good())
	{
		if (!btce::loadLinePrice(pricesStream))
		{
			ifstreamSkeepUntil(pricesStream, '\n');
		}
	}
	return (true);	
}

float	BitcoinExchange::getPrice(const std::string& date)
{
	return (this->getPrice(btce::dateStrToDays(date)));
}

float	BitcoinExchange::getPrice(day_count date)
{
	while (date > 0)
	{
		try
		{
			return(this->btcPrice.at(date));
		}
		catch (std::out_of_range& e) { }
		date--;
	}
	return (-1);
}

void	BitcoinExchange::printHistoryValues(const std::string& walletHistoryFileName)
{
	std::ifstream walletHistory(walletHistoryFileName.c_str());

	ifstreamSkeepUntil(walletHistory, '\n');
	while(walletHistory.good())
	{
		if (!this->printHistoryLineValue(walletHistory))
		{
			while(walletHistory.good() && walletHistory.peek() != '\n')
				walletHistory.get();
			if (walletHistory.peek() == '\n')
				walletHistory.get();
		}
	}
}

bool	BitcoinExchange::printHistoryLineValue(std::ifstream& walletHistory)
{
	std::string		dateStr;
	day_count		date;
	std::string		ammountStr;
	float			ammount;
	char			c;
	float			price;

	dateStr = dateStrFromFile(walletHistory, '|');
	if (dateStr.size() == 0 && !walletHistory.good())
		return (false);
	date = btce::dateStrToDays(dateStr);
	if (date == 0)
	{
		std::cout << "Invalid date: " << dateStr << ": "  << std::endl;
		return (false);
	}
	c = walletHistory.get();
	while(c != '\n')
	{
		ammountStr += c;
		c = walletHistory.get();
	}
	cleanBlank(ammountStr);
	if (!checkFloatStr(ammountStr))
	{
		std::cout << "Invalid ammount (min 0.0, max 1000.0): " << ammountStr << std::endl;;
		walletHistory.putback('\n');
		return(false);
	}
	ammount = std::atof(ammountStr.c_str());
	if (ammount < 0 || ammount > 1000)
	{
		std::cout << "Ammout out of range (min 0.0, max 1000.0): " << ammountStr << "." << std::endl;;
		walletHistory.putback('\n');
		return (false);
	}
	price = this->getPrice(date);
	if (price < 0)
	{
		std::cout << "Could not get price for date: " << dateStr << std::endl;
		walletHistory.putback('\n');
		return (false);
	}
	std::cout << dateStr << " => " << ammount << " = " << ammount * price << std::endl;
	return (true);
}

day_count BitcoinExchange::dateStrToDays(const std::string& strDate)
{
	day_count result;
	t_date date = BitcoinExchange::parseDate(strDate);

	result = 0;
	if (date.year == 0 || date.month == 0 || date.day == 0)
		return (0);
	if (date.month < 1 || date.month > 12)
		return (0);
	if (date.day > btce::monthToDays(date.month))
	{
		if ( !(btce::isLeap(date.year) && date.day == 29 && date.month == 2))
			return (0);
	}

	if (btce::isLeap(date.year) && date.month > 2)
		result += 1;
	date.year -= 1;
	result +=  ((date.year) / 400) * btce::DAYS_IN_400_YEARS;
	date.year %= 400;
	result +=  ((date.year) / 100) * btce::DAYS_IN_100_YEARS;
	date.year %= 100;
	result +=  ((date.year) / 4) * btce::DAYS_IN_4_YEARS;
	date.year %= 4;
	result +=  ((date.year)) * btce::DAYS_IN_1_YEARS;

	result += btce::monthAcumulatedDays(date.month);
	result += + date.day;

	return (result);
}

bool customAtoi(std::string::const_iterator& c, std::string::const_iterator end, unsigned int& dest)
{
	dest = 0;
	while (c != end && *c != '-')
	{
		if ( *c < '0' || *c > '9')
			return (false);
		dest *= 10; 
		dest += *c - '0'; 
		c++;
	}
	return (dest != 0);
}

t_date BitcoinExchange::parseDate(std::string strDate)
{
	std::string::const_iterator	c, end;
	t_date					date;
	
	c = strDate.begin();
	end = strDate.end();

	if (
		c != end && customAtoi(  c, end, date.year) 	&&
		c != end && customAtoi(++c, end, date.month) 	&&
		c != end && customAtoi(++c, end, date.day)		&&
		c == end
	)
		return (date);
	else
	{
		date.year = 0; date.month = 0; date.day = 0;
		return (date);
	}

}

std::string BitcoinExchange::dateStrFromFile(std::ifstream& file, char sep)
{
	char			c;
	std::string		dateStr;

	file.get(c);
	while(file.good() && c != sep && c!='\n')
	{
		dateStr.append(1, c);
		file.get(c);
	}
	if (c == '\n')				//Very wierd but works. if it gets till the end of line on datStrFrom file its an error. When an error ocurs its not suposed to change the line so I addid back right here. The error handling is somwhere else.
		file.putback('\n');
	cleanBlank(dateStr);

	return(dateStr);
}

day_count BitcoinExchange::parseDateKeyFromPricesFile(std::ifstream& prices, char sep)
{
	std::string		dateStr;
	day_count		date;

	dateStr = btce::dateStrFromFile(prices, sep);
	if (dateStr.size() == 0 && !prices.good())
		return (0);
	date = btce::dateStrToDays(dateStr);
	if (date == 0)
	{
		std::cout << "ERROR invalid date " << dateStr << std::endl; // TODO should not appear on first line
		return (0);
	}
	return (date);
}

float BitcoinExchange::parsePriceValFromPricesFile(std::ifstream& prices)
{
	char			c;
	std::string		priceStr;
	float			price;

	prices.get(c);
	while(prices.good() && c != '\n')
	{
		priceStr.append(1, c);
		prices.get(c);
	}
	try
	{
		price = atof(priceStr.c_str());
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "ERROR invalid price on date " << priceStr << std::endl;
		throw (e);
	}
	catch ( std::out_of_range& e)
	{
		std::cout << "ERROR invalid price on date " << priceStr << std::endl;
		throw (e);
	}
	return (price);
}

bool BitcoinExchange::loadLinePrice(std::ifstream& prices)
{
	day_count	date;
	float		price;

	date = btce::parseDateKeyFromPricesFile(prices, ',');
	if (date == 0 || !prices.good())
		return (false);
	try 
	{
		price = parsePriceValFromPricesFile(prices);
	}
	catch (std::invalid_argument& e)
	{
		return false;
	}
 	catch (std::out_of_range& e)
	{
		return false;
	}
	this->btcPrice[date] = price;
	return true;
}
