#pragma once
#include "Tile.h"
#include "Option.h"

class EntityTile : public Tile
{
private:
	std::vector<Option> _options;

public:
	EntityTile(const char& character, const Position& position, const std::vector<Option>& options, const std::string& tileColor = "\u001b[37m" /*white*/, const std::string& backgroundColor = "\u001b[30m"/*black*/);
	Option GetOption(const OPTION& optionName) const; // returns option with optionName = OPTION_ERROR if not found
	std::vector<Option> GetOptions() const;
};

