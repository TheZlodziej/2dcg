#pragma once
#include "Position.h"
#include <string>
#include "Exception.h"

class Tile {
protected:
	char _character;
	Position _position;
	std::string _tileColor;
	std::string _backgroundColor;

public:
	Tile(const char& character, const Position& position, const std::string& tileColor="\u001b[37m" /*white*/, const std::string& backgroundColor="\u001b[30m"/*black*/);
	char GetCharacter() const;
	void SetCharacter(const char& newCharacter);
	Position GetPosition() const;
	void SetPosition(const Position& position);
	std::string GetTileColor() const;
	std::string GetBackgroundColor() const;
	static std::string TileColor(const int& color);
	static std::string BackgroundColor(const int& color);
	void SetColor(const int& color);
	void SetBackgroundColor(const int& color);
};