#include "Option.h"

bool Option::Good() const
{
	return (this->optionName != OPTION::OPTION_ERROR);
}