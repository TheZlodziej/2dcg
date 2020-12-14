#pragma once
#include "Map.h"
#include "Player.h"
#include "Exception.h"
#include <fstream>
#include <sstream>
#include <Windows.h>

class Level
{
private:
	Map* _map = nullptr;
	std::vector<std::string> _maps; //for different rooms
	int _currentMapIndex;
	Player* _player = nullptr;
	std::vector<EntityTile> _optionTiles;

public:

	Level(std::istream& levelStream);
	~Level();
	void Load(std::istream& levelStream); //loads .level file
	void LoadMap(const int& mapIndex); //changes _currentMapIndex and set _map to new Map
	Player* GetPlayer();
	Map* GetMap();
	void AssignOptionTiles();
	std::vector<EntityTile> GetOptionTiles() const;

	//add layers here
	void Show()
	{
		_map->Show();
	}
};

