#ifndef	RPN_HPP
#define	RPN_HPP
#include <list>
#include <string>
#include <cstdlib>

class calculator : std::list<float>
{
	public:
		calculator() : std::list<float>(){};
		calculator(const calculator &orig) : std::list<float>(orig) {};
		calculator&	operator=(const calculator &orig) {(void) orig; return *this; };
		~calculator() {};

		float calculate(std::string);

	private:
		std::string::iterator		currOperand;
		std::string::iterator		endOperand;
		bool						doOperation();
};
#endif

/*
 * TODO
 * operator = is not right its not calling father
 * should assert there are the correct ammoutn of numbers and operators
 *
 */
