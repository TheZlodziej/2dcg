#include "EntityTile.h"

EntityTile::EntityTile(const char& character, const Position& position, const std::vector<Option>& options): Tile(character, position)
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