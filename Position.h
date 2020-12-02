#pragma once

struct Position {
	int x;
	int y;

	bool operator==(Position const& a) const;
	Position operator+(Position const& a);
	Position& operator+=(Position const& a);
	bool operator<(Position const& a) const;
	bool operator>(Position const& a) const;
};
