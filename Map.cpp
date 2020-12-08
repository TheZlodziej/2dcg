#include "Map.h"

Map::Map(const std::string filename)
{
	Load(filename);
}

void Map::Load(const std::string filename)
{
	std::ifstream file(filename);
	std::vector<std::vector<EntityTile>> InversedMap;

	if (file.good())
	{
		std::string tileData;
		file>>tileData;
		_width = std::stoi(tileData.substr(1, tileData.find(',') - 1));
		_height = std::stoi(tileData.substr(tileData.find(',') + 1, tileData.find(']') - tileData.find(',') - 1));

		for (int i=0; i < _height; i++)
		{
			std::vector<EntityTile> row;

			for (int j=0; j < _width; j++)
			{
				file>>tileData;
				row.push_back(EntityTile(tileData[0], (tileData[1] == 'c'), { j, i })); //if c == collidable
			}
			InversedMap.push_back(row);
		}

	}

	std::vector<std::vector<EntityTile>> map;
	for (int i = 0; i < _width; i++)
	{
		std::vector<EntityTile> column;
		
		for (int j = 0; j < _height; j++)
		{
			column.push_back(InversedMap[j][i]);
			if (InversedMap[j][i].Collidable())
			{
				_collidingPositions.push_back(InversedMap[j][i].GetPosition());
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

bool Map::InBoundings(Position position) const
{
	return (position.x >= 0 and position.x <= _width-1 and position.y >= 0 and position.y <= _height-1);
}

bool Map::CollidingWith(std::vector<Position> positions) const
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

bool Map::CollidingWith(EntityTile tile) const
{
	return CollidingWith(tile.GetPosition());
}

bool Map::CollidingWith(Position position) const
{
	return CollidingWith({ position });
}

bool Map::CollidingWith(std::vector<EntityTile> tiles) const
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

void Map::UpdateMap(std::vector<EntityTile> oldState, std::vector<EntityTile> newState)
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