#include "Tile.h"

Tile::Tile(const char& character, const Position& position)
{
	_character = character;
	_position = position;
}

char Tile::GetCharacter() const 
{ 
	return _character; 
}

void Tile::SetCharacter(const char& newCharacter) 
{ 
	_character = newCharacter; 
}

Position Tile::GetPosition() const
{
	return _position;
}

void Tile::SetPosition(const Position& newPosition)
{
	_position = newPosition;
}