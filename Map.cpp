#include "Map.h"

Map::Map(std::istream& mapStream)
{
	Load(mapStream);
}

void Map::Load(std::istream& mapStream)
{
	std::string mapSizeLine;
	std::getline(mapStream, mapSizeLine);
	std::stringstream mapSize(mapSizeLine);
	mapSize >> _width;
	mapSize >> _height;

	std::vector<std::vector<EntityTile>> map(_width, std::vector<EntityTile>(_height, EntityTile('*', { 0,0 }, {})));

	for (int i = 0; i < _height; i++)
	{
		//std::vector<EntityTile> row;
		std::string rowLine;
		std::getline(mapStream, rowLine);
		std::stringstream row(rowLine);

		for (int j = 0; j < _width; j++)
		{
			std::string tileData;
			if (!(row >> tileData))
			{
				throw new Exception(0, "[MAP] invalid file input - not enough tiles data.");
			}
			
			std::vector<Option> options;
			std::istringstream optionsStream(tileData.substr(1));
			std::string option;
			while (std::getline(optionsStream, option, '/'))
			{
				std::vector<int> arguments = {};
				OPTION optionName = OPTION::OPTION_ERROR;
				std::istringstream argumentsStream(option.substr(1));
				std::string argument;
				while (std::getline(argumentsStream, argument, ','))
				{
					arguments.push_back(std::stoi(argument));
				}

				switch (option[0])
				{
				case 'c':
					optionName = OPTION::COLLIDABLE;
					break;

				case 'n':
					optionName = OPTION::NON_COLLIDABLE;
					break;

				case 's':
					optionName = OPTION::SWITCH_MAP;
					break;

				case 'd':
					optionName = OPTION::DEAL_DMG;
					break;

				default:
					optionName = OPTION::OPTION_ERROR;
					break;
				}

				options.push_back({ optionName, arguments });
			}
			
			map[j][i] = EntityTile(tileData[0], { j, i }, options);

			if (map[j][i].GetOption(OPTION::COLLIDABLE).optionName != OPTION::OPTION_ERROR)
			{
				_collidingPositions.push_back({ j,i });
			}
		}
	}

	_map = map;
	_originalMap = _map;
}

EntityTile& Map::At(const Position& position)
{ 
	return _map[position.x][position.y]; 
}

std::vector<Position> Map::GetCollidingPositions() const
{
	return _collidingPositions;
}

bool Map::InBoundings(const Position& position) const
{
	return (position.x >= 0 and position.x <= _width-1 and position.y >= 0 and position.y <= _height-1);
}

bool Map::CollidingWith(const std::vector<Position>& positions) const
{
	for (Position const& positionA : positions)
	{
		for (Position const& positionB : _collidingPositions)
		{
			if ((positionA == positionB) or !InBoundings(positionA))
			{
				return true;
			}
		}
	}
	return false;
}

bool Map::CollidingWith(const EntityTile& tile) const
{
	return CollidingWith(tile.GetPosition());
}

bool Map::CollidingWith(const Position& position) const
{
	return CollidingWith({ position });
}

bool Map::CollidingWith(const std::vector<EntityTile>& tiles) const
{
	for (EntityTile const& tile : tiles)
	{
		if (CollidingWith(tile))
		{
			return true;
		}
	}
	return false;
}

void Map::UpdateMap(const std::vector<EntityTile>& oldState, const std::vector<EntityTile>& newState)
{
	for (EntityTile const& tile : oldState)
	{
		Position tilePosition = tile.GetPosition();
		At(tilePosition) = _originalMap[tilePosition.x][tilePosition.y];
		Draw(tilePosition, _originalMap[tilePosition.x][tilePosition.y].GetCharacter());
	}

	for (EntityTile const& tile : newState)
	{
		Position tilePosition = tile.GetPosition();
		At(tilePosition) = tile;
		Draw(tilePosition, tile.GetCharacter());
	}
}

int Map::GetHeight() const
{
	return _height;
}

int Map::GetWidth() const
{
	return _width;
}

void Map::GotoPosition(Position position) const
{
	COORD coord = { static_cast<short>(position.x), static_cast<short>(position.y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Map::Draw(const Position& position, const char& character) const
{
	GotoPosition(position);
	std::cout << character;
	GotoPosition({ 0, _height });
}

void Map::Show()
{
	system("cls");
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			std::cout << At({ x,y }).GetCharacter();
		}
		std::cout << "\n";
	}
}