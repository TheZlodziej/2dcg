#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "EntityTile.h"

//temp library for displaying
#include <iostream>

class Map
{
private:
	std::vector<std::vector<EntityTile>> _map;
	std::vector<std::vector<EntityTile>> _originalMap;
	std::vector<Position> _collidingPositions;
	int _width;
	int _height;

public:
	Map(const std::string filename);
	Tile& At(Position position); // return Tile at given position
	void Load(const std::string filename);
	std::vector<Position> GetCollidingPositions();
	void UpdateMap(std::vector<EntityTile> oldState, std::vector<EntityTile> newState);
	bool CollidingWith(std::vector<EntityTile> tiles) const;
	bool CollidingWith(std::vector<Position> positions) const;
	bool CollidingWith(Position position) const;
	bool CollidingWith(EntityTile tile) const;
	bool InBoundings(Position position) const;

	//temp display function
	void Show() 
	{
		system("cls");
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				std::cout << At({ x,y }).GetCharacter() << " ";
			}
			std::cout << "\n";
		}
	}
};

