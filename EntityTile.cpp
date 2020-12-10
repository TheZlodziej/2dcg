#include "EntityTile.h"

EntityTile::EntityTile(char character, bool collidable, Position position): Tile(character, collidable)
{
	_position = position;
}

Position EntityTile::GetPosition() const
{
	return _position;
}

void EntityTile::SetPosition(const Position& newPosition)
{
	_position = newPosition;
}