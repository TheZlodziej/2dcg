#include "Entity.h"

Entity::Entity(std::vector<EntityTile> body) 
{
	//SetCollidingPositions(); ??? does it need to be here
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

bool Entity::CollidingWith(const Entity* entity) const
{
	std::vector<Position> positions = entity->GetCollidingPositions();
	return CollidingWith(positions);
}

bool Entity::CollidingWith(const Map* map) const
{
	std::vector<Position> positions = map->GetCollidingPositions();
	return CollidingWith(positions);
}