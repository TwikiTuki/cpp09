#include <iostream>

template <typename contType>
void printContainer(contType cont)
{
	for
	(
		typename contType::iterator number = cont.begin();
		number != cont.end();
		number++
	)
	std::cout << *number << " ";
};

template <typename T > 
class sorter
{
	public:
		sorter<T>(){} ;
		sorter(T numbers) : numbers(numbers), initialNumbers(numbers) {};

		sorter(sorter& orig)
		{
			this->subsetSize = orig.subsetSize();
			this->initialNumbers = orig.initialNumbers;
			this->numbers = orig.numbers;
			this->subset0 = orig.subset0;
			this->subset1 = orig.subset1;
		};
		sorter& operator=(const sorter& orig)
		{
			this->subsetSize = orig.subsetSize();
			this->initialNumbers = orig.initialNumbers;
			this->numbers = orig.numbers;
			this->subset0 = orig.subset0;
			this->subset1 = orig.subset1;
			return *this;
		};

		~sorter() {};

		void print(void) { printContainer(this->numbers); };
		void printInitial(void) { printContainer(this->initialNumbers); };

		void push(const std::string& number)
		{
			std::string::const_iterator c = number.begin(), end = number.end();

			if (*c == '+')
				c++;
			for (; c != end; c++)
			{
				if (*c < '0' || *c > '9')
					throw std::exception();
			}
			this->push(atoi(number.c_str()));
		};
		void push(unsigned int num) { this->numbers.push_back(num); this->initialNumbers.push_back(num); };

		void sort(void)
		{	
			this->subsetSize = 1;
			while (subsetSize < numbers.size())
			{
				this->doIteration();
				this->subsetSize *= 2;
			}
		}

		void doIteration(void)
		{
			typename T::iterator number = numbers.begin();
			typename T::iterator end = numbers.end();
			typename T::iterator beginSet;

			while (number != end)
			{
				beginSet = number;	
				this->subset0.clear();
				this->subset1.clear();
				for (typename T::size_type i = 0; i < this->subsetSize && number != end; i++)
					this->subset0.push_back(*number++);
				for (typename T::size_type i = 0; i < this->subsetSize && number != end; i++)
					this->subset1.push_back(*number++);
				this->sortSet(beginSet);
			}
		}

		void sortSet(typename T::iterator& beginSet)
		{
			typename T::iterator num0 = this->subset0.begin();
			typename T::iterator end0 = this->subset0.end();
			typename T::iterator num1 = this->subset1.begin();
			typename T::iterator end1 = this->subset1.end();

			while (num0 != end0 || num1 != end1)
			{
				if (num1 == end1)
					*beginSet = *num0++;
				else if (num0 != end0 && *num0 < *num1)
					*beginSet = *num0++;
				else
					*beginSet = *num1++;
				beginSet++;
			}
		}

	private:
		T						initialNumbers;
		T						numbers;
		T						subset0;
		T						subset1;
		typename T::size_type	subsetSize;
};
