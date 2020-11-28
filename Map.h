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
	std::vector<Position> _collidingPositions;
	int _width;
	int _height;

public:
	Map(const std::string filename);
	Tile& At(Position position); // return Tile at given position
	void Load(const std::string filename);
	std::vector<Position> GetCollidingPositions();

	//temp display function
	void Show() 
	{
		system("cls");
		for (int x = 0; x < _width; x++)
		{
			for (int y = 0; y < _height; y++)
			{
				std::cout << At({ x,y }).GetCharacter() << " ";
			}
			std::cout << "\n";
		}
	}
};

