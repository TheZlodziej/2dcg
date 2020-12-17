#include "EntityTile.h"

EntityTile::EntityTile(const char& character, const Position& position, const std::vector<Option>& options, const std::string& tileColor, const std::string& backgroundColor): Tile(character, position, tileColor, backgroundColor)
{
	_options = options;
}

Option EntityTile::GetOption(const OPTION& optionName) const
{
	for (const Option& option : _options)
	{
		if (option.optionName == optionName)
		{
			return option;
		}
	}

	return { OPTION::OPTION_ERROR, {} };
}

std::vector<Option> EntityTile::GetOptions() const
{
	return _options;
}