#pragma once
#include "EntityTile.h"
#include "Map.h"
#include <vector>

class Entity
{
protected:
	std::vector<EntityTile> _body;
	std::vector<Position> _collidingPositions;

public:
	Entity(const std::vector<EntityTile>& body);
	std::vector<Position> GetCollidingPositions() const;
	void SetCollidingPositions();
	bool CollidingWith(const std::vector<Position>& positions) const;
	bool CollidingWith(const EntityTile& tile) const;
	bool CollidingWith(const Entity& entity) const;
	std::vector<EntityTile> GetBody() const;
	Position TopLeft() const; //get entity's top left position (as if it were square)
	Position BottomRight() const; //get entity's bottom right position (as if it were square)
	void SetPosition(Position& position);
};

