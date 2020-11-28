#pragma once
#include "EntityTile.h"
#include "Map.h"
#include <vector>
#include <algorithm>

class Entity
{
protected:
	std::vector<EntityTile> _body;
	std::vector<Position> _collidingPositions;

public:
	Entity(std::vector<EntityTile> body);
	std::vector<Position> GetCollidingPositions();
	bool CollidingWith(std::vector<Position> positions);
	bool CollidingWith(Entity* entity);
	bool CollidingWith(Map* map);
	std::vector<EntityTile> GetBody() const;
};

