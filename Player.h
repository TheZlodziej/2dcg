#pragma once
#include "Entity.h"

#include <iostream>
class Player : public Entity
{
protected:
	int _maxHp;
	int _currentHp;
	bool _dead;
	int _jumpHeight;
	Position _direction;

public:
	Player(const std::vector<EntityTile>& body, const int& maxHp, const int& jumpHeight);
	virtual ~Player();
	void LoseHp(const int& amount);
	void Die();
	bool Dead() const;
	void Update();
	int MaxHp() const;
	int Hp() const;
	void SetDirection(const Position& direction);
	Position GetDirection() const;
	int GetJumpHeight() const;
};

