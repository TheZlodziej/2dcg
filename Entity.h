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
	Entity(std::vector<EntityTile> body);
	std::vector<Position> GetCollidingPositions() const;
	void SetCollidingPositions();
	bool CollidingWith(std::vector<Position> positions);
	bool CollidingWith(Entity* entity);
	bool CollidingWith(Map* map); // colliding with colliding positions in map
	std::vector<EntityTile> GetBody() const;
};

