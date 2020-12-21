#pragma once
#include <vector>
#include "Position.h"

enum class OPTION {OPTION_ERROR=-1, COLLIDABLE=0, SWITCH_MAP=1, DEAL_DMG=2};

struct Option
{
	OPTION optionName;
	std::vector<int> arguments;
};