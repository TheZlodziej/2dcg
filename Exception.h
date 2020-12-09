#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

// #0 - map input error
//
//

class Exception
{
private:
	int _exceptionNumber;
	std::string _exceptionMessage;

public:
	Exception(int exceptionNumber, std::string exceptionMessage);
	void Display() const;
};

