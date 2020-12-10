#include "Tile.h"

Tile::Tile(const char& character, const bool& collidable)
{
	_character = character;
	_collidable = collidable;
}

char Tile::GetCharacter() const 
{ 
	return _character; 
}

void Tile::SetCharacter(const char& newCharacter) 
{ 
	_character = newCharacter; 
}

bool Tile::Collidable() const
{
	return _collidable;
}
