#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

// #0 - file input error
// #1 - file open error
// #2 - invalid index
// #3 - invalid color
// #4 - invalid option

class Exception
{
private:
	int _exceptionNumber;
	std::string _exceptionMessage;

public:
	Exception(int exceptionNumber, std::string exceptionMessage);
	void Display() const;
};

