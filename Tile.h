#pragma once
#include "Position.h"

class Tile {
protected:
	char _character;
	bool _collidable;

public:
	Tile(char character, bool collidable);
	char GetCharacter() const;
	void SetCharacter(char newCharacter);
	bool Collidable() const;
};