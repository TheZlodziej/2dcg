#include "Game.h"

Game::Game(std::vector<std::string> filenames, float frameRate)
{
	_levels = filenames;
	_frameRate = frameRate;
	_timer = new Timer();
}

Game::~Game()
{
	delete _currentLevel;
	delete _timer;
}

void Game::LoadLevel(int levelIndex)
{
	_currentLevelIndex = levelIndex;
	_currentLevel = new Level(_levels[_currentLevelIndex]);
}

bool Game::SelectionScreen()
{
	int selection = 0; // selection: 0=start; 1=change leve; 2=exit
	int optionsNumber = 3;
	int levelIndex = _currentLevelIndex;
	bool keyPressed = false;

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
		_timer->Tick();
		if (_timer->DeltaTime() >= 1.0f / _frameRate)
		{
			// up arrow
			if (GetAsyncKeyState(VK_UP) and 0x26)
			{
				keyPressed = true;
				selection = ((selection - 1) % optionsNumber) < 0 ? optionsNumber - 1 : selection - 1;
				printSelectionScreen();
			}

			// down arrow
			else if (GetAsyncKeyState(VK_DOWN) and 0x28)
			{
				keyPressed = true;
				selection = (selection + 1) % optionsNumber;
				printSelectionScreen();
			}

			// enter
			else if (GetAsyncKeyState(VK_RETURN) and 0x0D)
			{
				keyPressed = true;
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
			}

			if (keyPressed)
			{
				keyPressed = false;
				printSelectionScreen();
			}
		}
	}

	return false;
}

void Game::Update()
{
	return;
}

void Game::GameLoop()
{
	auto KeyboardInput = [this](bool& keyPressed) {
		Position direction = { 0,0 };
		
		if (GetAsyncKeyState(VK_UP) and 0x26)
		{
			//up arrow
			direction.x = -1;
			keyPressed = true;
		}

		if (GetAsyncKeyState(VK_DOWN) and 0x28)
		{
			//down arrow
			direction.x = 1;
			keyPressed = true;
		}

		if (GetAsyncKeyState(VK_RIGHT) and 0x27)
		{
			//right arrow
			direction.y = 1;
			keyPressed = true;
		}

		if (GetAsyncKeyState(VK_LEFT) and 0x25)
		{
			//left arrow
			direction.y = -1;
			keyPressed = true;
		}

		if (keyPressed)
		{
			_currentLevel->GetPlayer()->SetDirection(direction);
		}
	};

	auto Update = [this]() {
		std::vector<EntityTile> oldState = _currentLevel->GetPlayer()->GetBody();
		_currentLevel->GetPlayer()->Update();
		std::vector<EntityTile> newState = _currentLevel->GetPlayer()->GetBody();
		//check if move possible
		_currentLevel->GetMap()->UpdateMap(oldState, newState);
		_currentLevel->GetMap()->Show();
		//call draw function
	};


	while (!_currentLevel->GetPlayer()->Dead())
	{
		//std::thread keyboardInput(keyboardInputLambda, keyPressed);
		//std::thread update(updateLambda, keyPressed);
		_timer->Tick();
		
		if (_timer->DeltaTime() >= 1.0f / _frameRate)
		{
			bool keyPressed = false;
			KeyboardInput(keyPressed);

			if (keyPressed)
			{
				keyPressed = false;
				Update();
			}
		}
	}
}

void Game::Start()
{
	if (!SelectionScreen()) // false if exit was selected;
	{
		return;
	}

	_currentLevel->GetMap()->Show();
	GameLoop();
}