#include "Player.h"

Player::Player(std::vector<EntityTile> body, int maxHp) : Entity(body)
{
	_body = body;
	_maxHp = maxHp;
	_currentHp = _maxHp;
	_dead = false;
}

void Player::LoseHp(int amount)
{
	_currentHp -= amount;
	if (_currentHp <= 0)
	{
		Die();
	}
}

void Player::Die()
{
	_dead = true;
}

bool Player::CanMoveTo(Position desiredPosition, Position topLeftBounding, Position bottomRightBounding) const
{
	for (EntityTile const& tile : _body)
	{
		Position destinationPosition = { tile.TilePosition() + desiredPosition };
		if (destinationPosition < topLeftBounding or destinationPosition > bottomRightBounding)
		{
			return false;
		}
	}

	return true;
}

void Player::Move(Position direvtionVector)
{
	if (true)//change this to if can move to (...)
	{
		for (EntityTile& tile : _body)
		{
			tile.TilePosition() += direvtionVector;
		}
	}
}