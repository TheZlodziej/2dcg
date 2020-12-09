#include "Map.h"

Map::Map(const std::string& filename)
{
	Load(filename);
}

void Map::Load(const std::string& filename)
{
	std::ifstream file(filename);
	std::vector<std::vector<EntityTile>> inversedMap;

	if (file.good())
	{
		std::string tileData;
		file >> tileData;
		_width = std::stoi(tileData.substr(1, tileData.find(',') - 1));
		_height = std::stoi(tileData.substr(tileData.find(',') + 1, tileData.find(']') - tileData.find(',') - 1));

		for (int i = 0; i < _height; i++)
		{
			std::vector<EntityTile> row;
				
			for (int j = 0; j < _width; j++)
			{
				if (!(file >> tileData)) //getline & string stream instead
				{
					throw new Exception(0, "[MAP] '" + filename + "' has invalid input.");
				}
				row.push_back(EntityTile(tileData[0], (tileData[1] == 'c'), { j, i })); //if c == collidable
			}
			inversedMap.push_back(row);
			while ((file.peek() != '\n') && (file >> tileData)); //prevents oversized file input (ignores more characters than should be given)
		}
	}

	std::vector<std::vector<EntityTile>> map;
	for (int i = 0; i < _width; i++)
	{
		std::vector<EntityTile> column;

		for (int j = 0; j < _height; j++)
		{
			column.push_back(inversedMap[j][i]);
			if (inversedMap[j][i].Collidable())
			{
				_collidingPositions.push_back(inversedMap[j][i].GetPosition());
			}
		}


		map.push_back(column);
	}

	file.close();
	_map = map;
	_originalMap = _map;
}

Tile& Map::At(Position position)  
{ 
	return _map[position.x][position.y]; 
}

std::vector<Position> Map::GetCollidingPositions()
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
		_map[tilePosition.x][tilePosition.y] = _originalMap[tilePosition.x][tilePosition.y];
	}

	for (EntityTile const& tile : newState)
	{
		Position tilePosition = tile.GetPosition();
		_map[tilePosition.x][tilePosition.y] = tile;
	}
}