#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "EntityTile.h"
#include "Exception.h"

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
	Map(std::istream& mapStream);
	EntityTile& At(const Position& position);
	void Load(std::istream& mapStream);
	std::vector<Position> GetCollidingPositions() const;
	void UpdateMap(const std::vector<EntityTile>& oldState, const std::vector<EntityTile>& newState);
	bool CollidingWith(const std::vector<EntityTile>& tiles) const;
	bool CollidingWith(const std::vector<Position>& positions) const;
	bool CollidingWith(const Position& position) const;
	bool CollidingWith(const EntityTile& tile) const;
	bool InBoundings(const Position& position) const;
	int GetHeight() const;
	int GetWidth() const;

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

