#pragma once
#include "Entity.h"

#include <iostream>
class Player : public Entity
{
protected:
	int _maxHp;
	int _currentHp;
	bool _dead = false;

public:
	Player(std::vector<EntityTile> body, int maxHp);
	void LoseHp(int amount);
	void Die();
	void Move(Position directionVector);
	//bool CanMoveTo(Position desiredPosition, Position topLeftBounding, Position bottomRightBounding) const;
};

