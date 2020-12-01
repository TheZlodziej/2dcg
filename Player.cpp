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

bool Player::Dead() const
{
	return _dead;
}

//bool Player::CanMoveTo(Position desiredPosition, Position topLeftBounding, Position bottomRightBounding) const
//{
//	for (EntityTile const& tile : _body)
//	{
//		Position destinationPosition = { tile.TilePosition() + desiredPosition };
//		if (destinationPosition < topLeftBounding or destinationPosition > bottomRightBounding)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

void Player::SetDirection(Position direction)
{
	_direction = direction;
}

Position Player::GetDirection() const
{
	return _direction;
}

void Player::Update()
{
	for (EntityTile& tile : _body)
	{
		tile.SetPosition(tile.GetPosition() + _direction);
	}
}