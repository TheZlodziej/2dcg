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

	std::vector<std::vector<EntityTile>> map(_width, std::vector<EntityTile>(_height, EntityTile('*', false, {0,0})));

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
				throw new Exception(0, "[MAP] invalid file input - not enough data.");
			}
			
			map[j][i] = EntityTile(tileData[0], (tileData[1] == 'c'), { j, i }); //if c == collidable
			
			if (map[j][i].Collidable())
			{
				_collidingPositions.push_back({ j,i });
			}
		}
	}

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