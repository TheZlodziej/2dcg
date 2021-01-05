#pragma once
#include <vector>

enum class OPTION {OPTION_ERROR=-1, COLLIDABLE=0, SWITCH_MAP=1, DEAL_DMG=2, ADD_SCORE=3, EXIT_LEVEL=4};

struct Option
{
	OPTION optionName;
	std::vector<int> arguments;

	bool Good() const
	{
		return (this->optionName != OPTION::OPTION_ERROR);
	}
};