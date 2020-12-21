#include "Entity.h"

Entity::Entity(const std::vector<EntityTile>& body) 
{
	//SetCollidingPositions(); ??? does it need to be here
	_body = body;
	SetCollidingPositions();
}

void Entity::SetCollidingPositions()
{
	_collidingPositions = {};
	for (EntityTile const& tile : _body)
	{
		if (tile.GetOption(OPTION::COLLIDABLE).optionName != OPTION::OPTION_ERROR)
		{
			_collidingPositions.push_back(tile.GetPosition());
		}
	}
}

std::vector<EntityTile> Entity::GetBody() const
{
	return _body;
}

std::vector<Position> Entity::GetCollidingPositions() const
{
	return _collidingPositions;
}

bool Entity::CollidingWith(const std::vector<Position>& positions) const 
{
	for (Position const& positionA : positions)
	{
		for (Position const& positionB : GetCollidingPositions())
		{
			if (positionA == positionB)
			{
				return true;
			}
		}
	}

	return false;
}

bool Entity::CollidingWith(const EntityTile& tile) const
{
	return CollidingWith({ tile.GetPosition() });
}

bool Entity::CollidingWith(const Entity& entity) const
{
	return CollidingWith(entity.GetCollidingPositions());
}

void Entity::SetPosition(Position& position)
{
	Position deltaPosition = position - TopLeft();

	for (EntityTile& tile : _body)
	{
		tile.SetPosition(tile.GetPosition() + deltaPosition);
	}
}

Position Entity::TopLeft() const
{
	Position topLeft = _body[0].GetPosition();

	for (const Position& position : GetCollidingPositions())
	{
		if (position.x < topLeft.x)
		{
			topLeft.x = position.x;
		}

		if (position.y < topLeft.y)
		{
			topLeft.y = topLeft.y;
		}
	}

	return topLeft;
}

Position Entity::BottomRight() const
{
	Position bottomRight = _body[0].GetPosition();

	for (const Position& position : GetCollidingPositions())
	{
		if (position.x > bottomRight.x)
		{
			bottomRight.x = position.x;
		}

		if (position.y > bottomRight.y)
		{
			bottomRight.y = position.y;
		}
	}

	return bottomRight;
}