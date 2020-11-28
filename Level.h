#pragma once
#include "Map.h"
#include "Player.h"

class Level
{
private:
	Map* _map = nullptr;
	std::vector<std::string> _maps; //for different rooms
	int _currentMapIndex;
	Player* _player = nullptr;

public:

	Level(const std::string filename); //filename to level settings
	~Level();
	void Load(const std::string filename); // loads .level file
	void LoadMap(int mapIndex); // changes _currentMapIndex and set _map to new Map
	
	//temp tylko tutaj layers beda na pewno
	void Show()
	{
		_map->Show();
	}
};

