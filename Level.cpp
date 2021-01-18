#include "Level.h"

Level::Level(std::istream& levelStream)
{
	Load(levelStream);
	LoadMap(0);
	_score = 0;
	_ended = false;
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
		//player color player body tiles number (tiles:) //[//tile character//collidable//x,y//] //...// hp // jump height //

	std::string playerInput;
	std::getline(levelStream, playerInput);
	std::stringstream playerData(playerInput);

	int bodyTilesNumber;
	if (!(playerData >> bodyTilesNumber))
	{
		throw new Exception(0, "[LEVEL] (0) invalid file input - not enough player data.");
	}

	std::vector<EntityTile> body;
	for (int i = 0; i < bodyTilesNumber; i++)
	{
		std::string playerTileData;
		
		if (!(playerData >> playerTileData))
		{
			throw new Exception(0, "[LEVEL] (1) invalid file input - not enough player data.");
		}

		char character = playerTileData[1];

		Position position = { std::stoi(playerTileData.substr(2, playerTileData.find(',') - 2)), std::stoi(playerTileData.substr(playerTileData.find(',') + 1, playerTileData.find(']') - playerTileData.find(',') - 1)) };
		body.push_back(EntityTile(character, position, { { OPTION::COLLIDABLE, {} } }));
	}

	int maxHp;
	if (!(playerData >> maxHp))
	{
		throw new Exception(0, "[LEVEL] (2) invalid file input - not enough player data.");
	}

	int jumpHeight;
	if (!(playerData >> jumpHeight))
	{
		throw new Exception(0, "[LEVEL] (3) invalid file input - not enough player data.");
	}

	_player = new Player(body, maxHp, jumpHeight);
	
	//highscore
	std::string scoreInput;
	std::getline(levelStream, scoreInput);
	std::stringstream scoreData(scoreInput);

	int highscore;
	if (!(scoreData >> highscore))
	{
		throw new Exception(0, "[LEVEL] (4) invalid file input - not enough level data");
	}

	_highscore = highscore;
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

void Level::AddScore(const int& amount)
{
	_score += amount;
}

int Level::GetScore() const
{
	return _score;
}

void Level::End()
{
	_ended = true;
}

bool Level::Ended() const
{
	return _ended;
}

int Level::GetHighscore() const
{
	return _highscore;
}

void Level::SetHighscore(std::iostream& levelStream)
{
	_highscore = _score;
	std::string lines;
	std::getline(levelStream, lines);

	std::vector<std::string> fileData;

	for (int i = 0; i <= /*for player data too*/ std::stoi(lines); i++)
	{
		std::string temp;
		std::getline(levelStream, temp);
		fileData.push_back(temp);
	}

	//write to file
	levelStream.clear();
	levelStream.seekg(0, std::ios::beg);

	levelStream << (lines + "\n");
	for (const std::string& line : fileData)
	{
		levelStream << (line + "\n");
	}
	levelStream << _highscore;
}
