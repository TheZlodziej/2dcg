#include "Entity.h"

Entity::Entity(std::vector<EntityTile> body) 
{
	for (EntityTile const& tile : _body)
	{
		if (tile.Collidable())
		{
			_collidingPositions.push_back(tile.GetPosition());
		}
	}
}

std::vector<EntityTile> Entity::GetBody() const
{
	return _body;
}

std::vector<Position> Entity::GetCollidingPositions()
{
	return _collidingPositions;
}

bool Entity::CollidingWith(std::vector<Position> positions) 
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

bool Entity::CollidingWith(Entity* entity) 
{
	std::vector<Position> positions = entity->GetCollidingPositions();
	return CollidingWith(positions);
}

bool Entity::CollidingWith(Map* map) 
{
	std::vector<Position> positions = map->GetCollidingPositions();
	return CollidingWith(positions);
}