#pragma once

struct Position {
	int x;
	int y;

	bool operator==(Position const& a) const
	{
		return (this->x == a.x and this->y == a.y);
	}

	Position operator+(Position const& a)
	{
		return { this->x + a.x, this->y + a.y };
	}

	Position& operator+=(Position const& a)
	{
		this->x += a.x;
		this->y += a.y;
		return *this;
	}

	bool operator<(Position const& a) const
	{
		return (this->x < a.x or this->y < a.y);
	}

	bool operator>(Position const& a) const
	{
		return (this->x > a.x or this->y > a.y);
	}
};
