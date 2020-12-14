#pragma once
#include <vector>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "Level.h"
#include "Timer.h"

class Game
{
private:
	std::vector<std::string> _levels;
	Level* _currentLevel = nullptr;
	int _currentLevelIndex;
	Timer* _timer = nullptr;
	float _frameRate;

public:
	Game(const std::vector<std::string>& filenames, const float& frameRate=30);
	~Game();
	void LoadLevel(const int& levelIndex);
	void GameLoop();
	void Update(const Position& direction);
	void KeyboardInput(bool& keyPressed, Position& direction);
	bool MovePossible(std::vector<Position>& positions, const Position& direction);
	void Start();
	void Draw();
	void CheckOptions();
	bool SelectionScreen();
};

