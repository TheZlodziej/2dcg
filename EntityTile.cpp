#include "EntityTile.h"

EntityTile::EntityTile(char character, bool collidable, Position position): Tile(character, collidable)
{
	_position = position;
}

Position EntityTile::TilePosition() const
{
	return _position;
}