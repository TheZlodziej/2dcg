#pragma once
#include <vector>
#include <Windows.h>
#include <thread>
#include "Level.h"
#include "Timer.h"

class Game
{
protected:
	std::vector<std::string> _levels;
	Level* _currentLevel = nullptr;
	int _currentLevelIndex;
	Timer* _timer = nullptr;
	float _frameRate;

public:
	Game(std::vector<std::string> filenames, float frameRate=30);
	~Game();
	void LoadLevel(int levelIndex);
	void Update();
	void GameLoop();
	void Start();
	bool SelectionScreen();
};

