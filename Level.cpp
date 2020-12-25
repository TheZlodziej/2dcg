#include "Level.h"

Level::Level(std::istream& levelStream)
{
	Load(levelStream);
	LoadMap(0);
	_gold = 0;
}

Level::~Level()
{
	delete _map;
	delete _player;
}

void Level::Load(std::istream& levelStream)
{

	// maps number
	// map path
	// player
	// ...

	//map
		//maps number
		//maps paths

	std::string mapsNumberLine;
	std::getline(levelStream, mapsNumberLine);
	int mapsNumber = std::stoi(mapsNumberLine);
	//check if correct map data

	for (int i = 0; i < mapsNumber; i++)
	{
		std::string mapPath;
		std::getline(levelStream, mapPath);
		_maps.push_back(mapPath);
	}

	//player
		//player body tiles number (tiles:) //[//tile character//collidable//x,y//] //...// hp//

	std::string playerInput;
	std::getline(levelStream, playerInput);
	std::stringstream playerData(playerInput);

	int bodyTilesNumber;
	if (!(playerData >> bodyTilesNumber))
	{
		throw new Exception(0, "[LEVEL] invalid file input - not enough player data.");
	}

	std::vector<EntityTile> body;
	for (int i = 0; i < bodyTilesNumber; i++)
	{
		std::string playerTileData;
		
		if (!(playerData >> playerTileData))
		{
			throw new Exception(0, "[LEVEL] invalid file input - not enough player data.");
		}

		char character = playerTileData[1];

		Position position = { std::stoi(playerTileData.substr(2, playerTileData.find(',') - 2)), std::stoi(playerTileData.substr(playerTileData.find(',') + 1, playerTileData.find(']') - playerTileData.find(',') - 1)) };
		body.push_back(EntityTile(character, position, { { OPTION::COLLIDABLE, {} } }));
	}

	int maxHp;
	if (!(playerData >> maxHp))
	{
		throw new Exception(0, "[LEVEL] invalid file input - not enough player data.");
	}

	_player = new Player(body, maxHp);
	//...
}

void Level::LoadMap(const int& mapIndex)
{
	_currentMapIndex = mapIndex;
	if (_currentMapIndex >= static_cast<int>(_maps.size()) or _currentMapIndex < 0)
	{
		throw new Exception(2, "[MAP] map index out of size.");
	}

	std::ifstream mapStream(_maps[_currentMapIndex]);
	
	if (mapStream.good())
	{
		_map = new Map(mapStream);
		AssignOptionTiles();
	}
	else
	{
		throw new Exception(1, "[MAP] file open error.");
	}

	mapStream.close();
}

Player* Level::GetPlayer()
{
	return _player;
}

Map* Level::GetMap()
{
	return _map;
}

void Level::AssignOptionTiles()
{
	_optionTiles = {};

	for (int i = 0; i < _map->GetWidth(); i++)
	{
		for (int j = 0; j < _map->GetHeight(); j++)
		{
			if (_map->At({ i, j }).GetOptions().size() > 0)
			{
				_optionTiles.push_back(_map->At({ i,j }));
			}
		}
	}
}

std::vector<EntityTile> Level::GetOptionTiles() const
{
	return _optionTiles;
}

void Level::AddGold(const int& amount)
{
	_gold += amount;
}

int Level::GetGold() const
{
	return _gold;
}
