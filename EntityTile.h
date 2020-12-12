#pragma once
#include "Tile.h"
#include "Option.h"

class EntityTile : public Tile
{
private:
	std::vector<Option> _options;

public:
	EntityTile(const char& character, const Position& position, const std::vector<Option>& options);
	Option GetOption(const OPTION& optionName) const; // returns option with optionName = OPTION_ERROR if not found
};

