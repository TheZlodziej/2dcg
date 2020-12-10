#pragma once
#include "Map.h"
#include "Player.h"
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

public:

	Level(std::istream& levelStream); //filename to level settings
	~Level();
	void Load(std::istream& levelStream); // loads .level file
	void LoadMap(int mapIndex); // changes _currentMapIndex and set _map to new Map
	Player* GetPlayer();
	Map* GetMap();

	//temp tylko tutaj layers beda na pewno
	void Show()
	{
		_map->Show();
	}
};

