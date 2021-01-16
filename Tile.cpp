#include "Tile.h"

Tile::Tile(const char& character, const Position& position, const std::string& tileColor, const std::string& backgroundColor)
{
	_character = character;
	_position = position;
	_tileColor = tileColor;
	_backgroundColor = backgroundColor;
}

Tile::~Tile() {}

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

std::string Tile::TileColor(const int& color)
{
	switch(color)
	{
	case 0: //black
		return "\u001b[30m";

	case 1: //red
		return "\u001b[31m";

	case 2: //green
		return "\u001b[32m";

	case 3: //yellow
		return "\u001b[33m";

	case 4: //blue
		return "\u001b[34m";

	case 5: //magenta
		return "\u001b[35m";

	case 6: //cyan
		return "\u001b[36m";

	case 7: //white
		return "\u001b[37m";

	case 8: //brown
		return "\u001b[38;5;130m";

	case 9: //light blue
		return "\u001b[38;5;45m";

	default:
		throw new Exception(3, "[TILE BACKGROUND COLOR] invalid tile background color.");
		break;
	}
}

std::string Tile::BackgroundColor(const int& color)
{
	switch (color)
	{
	case 0: //black
		return "\u001b[40m";

	case 1: //red
		return "\u001b[41m";

	case 2: //green
		return "\u001b[42m";

	case 3: //yellow
		return "\u001b[43m";

	case 4: //blue
		return "\u001b[44m";

	case 5: //magenta
		return "\u001b[45m";

	case 6: //cyan
		return "\u001b[46m";

	case 7: //white
		return "\u001b[47m";

	case 8: //brown
		return "\u001b[48;5;130m";

	case 9: //light blue
		return "\u001b[48;5;45m";

	default:
		throw new Exception(3, "[TILE BACKGROUND COLOR] invalid tile background color.");
		break;
	}
}

void Tile::SetColor(const int& color)
{
	_tileColor = TileColor(color);
}

void Tile::SetBackgroundColor(const int& color)
{
	_backgroundColor = BackgroundColor(color);
}