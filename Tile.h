#pragma once
#include "Position.h"

class Tile {
protected:
	char _character;
	Position _position;

public:
	Tile(const char& character, const Position& position);
	char GetCharacter() const;
	void SetCharacter(const char& newCharacter);
	Position GetPosition() const;
	void SetPosition(const Position& position);
};