#pragma once
#include "Entity.h"

#include <iostream>
class Player : public Entity
{
protected:
	int _maxHp;
	int _currentHp;
	bool _dead;
	Position _direction;

public:
	Player(const std::vector<EntityTile>& body, const int& maxHp);
	void LoseHp(const int& amount);
	void Die();
	bool Dead() const;
	void Update();
	int MaxHp() const;
	int Hp() const;
	void SetDirection(const Position& direction);
	Position GetDirection() const;
};

