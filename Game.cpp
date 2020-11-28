#include "Game.h"
#include <Windows.h>
#include <thread>
#include <chrono>

Game::Game(std::vector<std::string> filenames)
{
	_levels = filenames;
}

Game::~Game()
{
	delete _currentLevel;
}

void Game::LoadLevel(int levelIndex)
{
	_currentLevelIndex = levelIndex;
	_currentLevel = new Level(_levels[_currentLevelIndex]);
}

void Game::KeyboardInput()
{
	return; //this will be lambda inside Update()
}

void Game::Update()
{
	return; //move this into Start()?
}

bool Game::SelectionScreen()
{
	int selection = 0; // selection: 0=start; 1=change leve; 2=exit
	int optionsNumber = 3;
	int levelIndex = _currentLevelIndex;

	auto printSelectionScreen = [&selection, &levelIndex]() {
		system("cls");
		std::cout << "//..........................................//" << std::endl;
		std::cout << "//.................................Level:" << levelIndex << "..//" << std::endl;
		std::cout << "//................." << (selection == 0 ? "[Start]" : ".Start.") << "..................//" << std::endl;
		std::cout << "//............." << (selection == 1l ? "[Change level]" : ".Change level.") << "...............//" << std::endl;
		std::cout << "//................." << (selection == 2 ? "[Exit]" : ".Exit.") << "...................//" << std::endl;
		std::cout << "//..........................................//" << std::endl;
		std::cout << "//..........................................//";
	};

	printSelectionScreen();

	while (true)
	{

		// up arrow
		if (GetAsyncKeyState(VK_UP) and 0x26)
		{
			selection = ((selection - 1) % optionsNumber) < 0 ? optionsNumber - 1 : selection - 1;
			printSelectionScreen();
		}

		// down arrow
		else if (GetAsyncKeyState(VK_DOWN) and 0x28)
		{
			selection = (selection + 1) % optionsNumber;
			printSelectionScreen();
		}

		// enter
		else if (GetAsyncKeyState(VK_RETURN) and 0x0D)
		{
			switch (selection)
			{
			case 0:
				LoadLevel(levelIndex);
				return true;

			case 1:
				levelIndex = (levelIndex + 1) % _levels.size();
				break;

			case 2:
				return false;
			}

			printSelectionScreen();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // sleep to avoid multiple input
	}
}

void Game::Start()
{
	if (!SelectionScreen()) // false if exit was selected;
	{
		return;
	}

	//game loop
	_currentLevel->Show();
}