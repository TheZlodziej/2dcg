#include "Tile.h"

Tile::Tile(char character, bool collidable)
{
	_character = character;
	_collidable = collidable;
}

char Tile::GetCharacter() const 
{ 
	return _character; 
}

void Tile::SetCharacter(char newCharacter) 
{ 
	_character = newCharacter; 
}

bool Tile::Collidable() const
{
	return _collidable;
}
