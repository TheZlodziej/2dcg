#include "Map.h"

Map::Map(const std::string filename)
{
	Load(filename);
}

void Map::Load(const std::string filename)
{
	std::ifstream file(filename);
	std::vector<std::vector<EntityTile>> map;

	if (file.good())
	{
		std::string tileData;
		file>>tileData;
		int width = std::stoi(tileData.substr(1, tileData.find(',') - 1));
		int height = std::stoi(tileData.substr(tileData.find(',') + 1, tileData.find(']') - tileData.find(',') - 1));

		for (int i=0; i<height; i++)
		{
			std::vector<EntityTile> column;

			for (int j=0; j<width; j++)
			{
				file>>tileData;
				column.push_back(EntityTile(tileData[0], (tileData[1] == 'c'), {j, i})); //if c == collidable
				
				if (tileData[1] == 'c')
					_collidingPositions.push_back({ j,i });
			}

			map.push_back(column);
		}
	}

	file.close();
	_map = map;
	_height = _map[0].size();
	_width = _map.size();
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