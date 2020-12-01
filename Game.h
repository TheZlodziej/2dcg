#pragma once
#include <vector>
#include "Level.h"

class Game
{
protected:
	std::vector<std::string> _levels;
	Level* _currentLevel = nullptr;
	int _currentLevelIndex;

public:
	Game(std::vector<std::string> filenames);
	~Game();
	void LoadLevel(int levelIndex);
	void Update();
	void GameLoop();
	void Start();
	bool SelectionScreen();
};

