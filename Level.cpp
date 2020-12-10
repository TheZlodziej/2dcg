#include "Level.h"

Level::Level(std::istream& levelStream)
{
	Load(levelStream);
	LoadMap(0);
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

	for (int i = 0; i < mapsNumber; i++)
	{
		std::string mapPath;
		std::getline(levelStream, mapPath); //possible blank space in path
		_maps.push_back(mapPath);
	}

	//player
		//player body tiles number (tiles:) //[//tile character//collidable//x,y//] //...// hp//

	std::string playerInput;
	std::getline(levelStream, playerInput);
	std::stringstream playerData(playerInput);

	int bodyTilesNumber;
	playerData >> bodyTilesNumber;

	std::vector<EntityTile> body;
	for (int i = 0; i < bodyTilesNumber; i++)
	{
		std::string playerTileData;
		playerData >> playerTileData;

		char character = playerTileData[1];
		bool collidable = playerTileData[2] == 'c';
		Position position = { std::stoi(playerTileData.substr(3, playerTileData.find(',') - 3)), std::stoi(playerTileData.substr(playerTileData.find(',') + 1, playerTileData.find(']') - playerTileData.find(',') - 1)) };
		body.push_back(EntityTile(character, collidable, position));
	}

	int maxHp;
	playerData >> maxHp;

	_player = new Player(body, maxHp);
	//...
}

void Level::LoadMap(int mapIndex)
{
	_currentMapIndex = mapIndex;

	std::ifstream mapStream(_maps[_currentMapIndex]);
	if (mapStream.good())
	{
		_map = new Map(mapStream);
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