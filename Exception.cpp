#include "Exception.h"

Exception::Exception(int exceptionNumber, std::string exceptionMessage)
{
	_exceptionNumber = exceptionNumber;
	_exceptionMessage = exceptionMessage;
}

void Exception::Display() const
{
	system("cls");
	std::cout << "\nERROR NUMBER: " << _exceptionNumber << ".\nMESSAGE: " << _exceptionMessage << "\n";
}

void Exception::Unknown()
{
	system("cls");
	std::cout << "\nUNKNOWN ERROR.";
}