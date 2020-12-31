#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "EntityTile.h"
#include "Exception.h"
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
	EntityTile& AtOriginal(const Position& position);
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
	void GotoPosition(const Position& position) const;
	void Draw(const EntityTile& tile) const;
	void Show();
	void SetCharacterAt(const Position& position, const char& character); //sets original character at position to given character
	void RemoveOptionAt(const Position& postiion, const OPTION& optionName); //removes an option with given option name from original map at given position
	void SetTileColorAt(const Position& position, const int& color);
	void SetTileBackgroundColorAt(const Position& position, const int& color);
};

