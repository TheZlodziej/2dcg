#include "Tile.h"

Tile::Tile(const char& character, const Position& position, const std::string& tileColor, const std::string& backgroundColor)
{
	_character = character;
	_position = position;
	_tileColor = tileColor;
	_backgroundColor = backgroundColor;
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

std::string Tile::GetTileColor() const
{
	return _tileColor;
}

std::string Tile::GetBackgroundColor() const
{
	return _backgroundColor;
}