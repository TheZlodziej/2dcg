#pragma once
#include <vector>
#include "Position.h"

enum class OPTION {OPTION_ERROR=-1, COLLIDABLE=0, NON_COLLIDABLE=1, SWITCH_MAP=2, STARTING_POSITION=3};

struct Option
{
	OPTION optionName;
	std::vector<int> arguments;
};