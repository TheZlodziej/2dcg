#pragma once
#include "Tile.h"
#include "Position.h"

class EntityTile : public Tile
{
protected:
	Position _position;
public:
	EntityTile(char character, bool collidable, Position position);
	Position GetPosition() const;
	void SetPosition(const Position& position);
};

