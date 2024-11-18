#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <cstdlib>
#include "PmergeMe.hpp"


timespec timespecDiff(const timespec& tl, const timespec& tr)
{
	timespec result = tl;

	if (tl.tv_sec < tr.tv_sec ||
		(tl.tv_sec == tr.tv_sec && tl.tv_nsec < tr.tv_nsec)
	)
		return (tl);

	if (tl.tv_nsec < tr.tv_nsec)
	{
		result.tv_sec -= tr.tv_sec + 1;
		result.tv_nsec = 1000000000 - tr.tv_nsec + tl.tv_nsec;
	}
	else 
	{
		result.tv_sec -= tr.tv_sec;
		result.tv_nsec -= tr.tv_nsec;
	}
	return (result);
}

template<typename contType>
timespec doTest(std::string inpNumbers, contType& queue)
{
	std::stringstream	numbers(inpNumbers);
	std::string 		number;
	struct timespec		start, end;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	while (numbers >> number)
		queue.push(number);
	queue.sort();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	return (timespecDiff(end, start));
}

int main(int argc, char **argv)
{
	sorter<std::deque<int> >			queueSorter;
	sorter<std::vector<int> >			vectorSorter;
	std::string							numbers;

	if (argc < 2)
	{
		std::cout << "ERROR" << std::endl;
		return (1);
	}	
	for (int i = 1; i < argc; i++)
	{
		numbers = numbers + std::string(" ") + std::string(argv[i]);
		numbers.erase(numbers.size(), 1);
	}
	std::cout << "NUMBERS : " << numbers << std::endl;
	struct timespec duration0;
	struct timespec duration1;
	try
	{
		duration0 = doTest(numbers, queueSorter);
		duration1 = doTest(numbers, vectorSorter);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR" << std::endl;
		return (1);
	}
	std::cout << "Before: " ; queueSorter.printInitial(); std::cout << std::endl << std::endl;
	std::cout << "After: " ; queueSorter.print(); std::cout << std::endl;
	std::cout << "Time to process with queue: " << duration0.tv_sec << ", " <<  
				duration0.tv_nsec << "ns." << std::endl;
	std::cout << "Time to process with vector: " << duration1.tv_sec << ", " <<  
				duration1.tv_nsec << "ns." << std::endl;
	std::cout << std::endl;
}
