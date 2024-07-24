#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

# include <string>
# include <map>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

# define DAYTS_IN_1_YEAR 365
# define DAYTS_IN_4_YEAR 1461
# define DAYTS_IN_400_YEAR 146099

typedef unsigned int day_count;

typedef struct s_date{
	day_count year;
	day_count month;
	day_count day;
} t_date;

class BitcoinExchange
{
	public:
		BitcoinExchange(){};
		BitcoinExchange(const BitcoinExchange  &orig);
		BitcoinExchange& operator=(const BitcoinExchange &orig);
		~BitcoinExchange(){};

		static day_count		dateStrToDays(const std::string& strDate);
		static t_date			parseDate(std::string strDate);
		static					std::map<day_count, day_count> INITIALIZE_DAYS_IN_A_MONTH();
		static					bool isLeap(day_count year);
		static day_count		monthToDays(day_count month);
		static day_count 		monthAcumulatedDays(day_count month);
		static std::string 		dateStrFromFile(std::ifstream& file, char sep);

		bool					loadPrices(std::string fileName);
		float					getPrice(const std::string& date);
		float					getPrice(day_count date);
		void					printHistoryValues(const std::string& walletHistory);
		bool					printHistoryLineValue(std::ifstream& walletHistory);

	private:
		static const day_count						DAYS_IN_1_YEARS = 365;
		static const day_count						DAYS_IN_4_YEARS = 1461;
		static const day_count						DAYS_IN_100_YEARS = 36524;
		static const day_count						DAYS_IN_400_YEARS = 146097;

		const static std::map<day_count, day_count> DAYS_IN_A_MONTH;


		static		day_count parseDateKeyFromPricesFile(std::ifstream& fineName, char sep);
		static		float parsePriceValFromPricesFile(std::ifstream& fineName);

		std::map<day_count, float>					btcPrice;
		bool		loadLinePrice(std::ifstream& prices);

};

typedef BitcoinExchange btce;

#endif
