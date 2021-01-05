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
	bool _playerJumping;
	int _jumpingFrame;
	int _jumpingMaxFrame;

public:
	Game(const std::vector<std::string>& filenames, const float& frameRate=30);
	~Game();
	void LoadLevel(const int& levelIndex);
	void GameLoop();
	void Update(const Position& direction);
	void KeyboardInput(Position& direction);
	bool MovePossible(std::vector<Position>& positions, const Position& direction);
	void Start();
	void CheckOptions();
	void HUD();
	bool SelectionScreen();
	void ApplyGravity();
	void Jump();
	void Move(const Position& direction);
	void LostScreen();
	void RestartLevel();
	void HowToPlayScreen();
	void WonScreen();
	int Digits(int number); //returns the length of number (necessary for displaying numbers [to make it look pretty])
};

