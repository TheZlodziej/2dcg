#pragma once
#include "Position.h"

class Tile {
protected:
	char _character;
	bool _collidable;

public:
	Tile(const char& character, const bool& collidable);
	char GetCharacter() const;
	void SetCharacter(const char& newCharacter);
	bool Collidable() const;
};