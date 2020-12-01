#pragma once
#include "Entity.h"

#include <iostream>
class Player : public Entity
{
protected:
	int _maxHp;
	int _currentHp;
	bool _dead = false;
	Position _direction;

public:
	Player(std::vector<EntityTile> body, int maxHp);
	void LoseHp(int amount);
	void Die();
	bool Dead() const;
	void Update();
	void SetDirection(Position direction);
	Position GetDirection() const;
	//bool CanMoveTo(Position desiredPosition, Position topLeftBounding, Position bottomRightBounding) const;
};

