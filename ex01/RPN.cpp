#include "RPN.hpp"
#include <exception>
#include <iostream>

void cleanBlank(std::string& str)
{
	for (std::string::iterator c = str.begin(), end = str.end(); c !=end;)
	{  
		if (*c == ' ' || *c == '\t')
			str.erase(c);
		else
			c++;
	}
}

float calculator::calculate(std::string input)
{
	cleanBlank(input);
	this->currOperand = input.begin();
	this->endOperand = input.end();
	while(this->currOperand != this->endOperand && *this->currOperand)
	{
		if (*this->currOperand <= '9' && *this->currOperand >= '0')
			this->push_front(*this->currOperand - '0');
		else if(doOperation())
			;
		else
		{
			throw (std::exception());
		}
		currOperand++;
	}
	if (this->size() != 1)
		throw (std::exception());
	return this->front();
}

bool calculator::doOperation()
{
	if (this->size() < 2)
		throw (std::exception());
	float operand0 = this->front(); this->pop_front();
	float operand1 = this->front(); this->pop_front();
	switch (*this->currOperand)
	{
		case '+':
			this->push_front(operand1 + operand0);
			return true;
		case '-':
			this->push_front(operand1 - operand0);
			return true;
		case '*':
			this->push_front(operand1 * operand0);
			return true;
		case '/':
			this->push_front(operand1 / operand0);
			return true;
	}
	return false;
}
