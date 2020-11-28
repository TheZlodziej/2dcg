#include "Level.h"

Level::Level(const std::string filename)
{
	Load(filename);
	LoadMap(0);
}

Level::~Level()
{
	delete _map;
	delete _player;
}

void Level::Load(const std::string filename)
{
	std::ifstream file(filename);

	if (file.good())
	{
		// maps number
		// map path
		// player
		// ...

		//map
			//maps number
			//maps paths
		int mapsNumber;
		file >> mapsNumber;
		file.ignore(); //for getline()

		for (int i = 0; i < mapsNumber; i++)
		{
			std::string mapPath;
			std::getline(file, mapPath); //possible blank space in path
			_maps.push_back(mapPath);
		}

		//player
			//player body tiles number
			//player body tiles
				//[//tile character//collidable//x,y//]//...// hp//

		int bodyTilesNumber;
		file >> bodyTilesNumber;

		std::string playerData;
		file >> playerData;

		std::vector<EntityTile> body;
		for (int i = 0; i < bodyTilesNumber; i++)
		{
			body.push_back(EntityTile(playerData[1], playerData[2], { std::stoi(playerData.substr(3, playerData.find(',') - 3)), std::stoi(playerData.substr(playerData.find(',') + 1, playerData.find(']') - playerData.find(',') - 1)) }));
			playerData = playerData.substr(0, playerData.find(']')+1);
		}

		int maxHp;
		file >> maxHp;

		_player = new Player(body, maxHp);

		//...
	}

	file.close();
}

void Level::LoadMap(int mapIndex)
{
	_currentMapIndex = mapIndex;
	_map = new Map(_maps[_currentMapIndex]);
	
}
