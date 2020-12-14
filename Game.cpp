#include "Game.h"

Game::Game(const std::vector<std::string>& filenames, const float& frameRate)
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

void Game::LoadLevel(const int& levelIndex)
{
	_currentLevelIndex = levelIndex;
	
	if (_currentLevelIndex >= int(_levels.size()) or _currentLevelIndex < 0)
	{
		throw new Exception(3, "[LEVEL] level index out of size.");
	}

	std::ifstream levelStream(_levels[_currentLevelIndex]);

	if (levelStream.good())
	{
		_currentLevel = new Level(levelStream);
	}
	else
	{
		throw new Exception(1, "[LEVEL] file open error");
	}

	levelStream.close();
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
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				keyPressed = false;
				printSelectionScreen();
			}
		}
	}

	return false;
}

bool Game::MovePossible(std::vector<Position>& positions, const Position& direction)
{
	for (Position& position : positions)
	{
		position += direction;
	}

	return !_currentLevel->GetMap()->CollidingWith(positions);
}

void Game::CheckOptions()
{
	for (const EntityTile& tile : _currentLevel->GetOptionTiles())
	{
		if (_currentLevel->GetPlayer()->CollidingWith(tile))
		{
			Option option = tile.GetOption(OPTION::SWITCH_MAP);
			if (option.optionName != OPTION::OPTION_ERROR)
			{
				Position newPlayerPosition = { option.arguments[1], option.arguments[2] };
				_currentLevel->LoadMap(option.arguments[0]);
				_currentLevel->GetPlayer()->SetPosition(newPlayerPosition);
				Update({0,0});
				_currentLevel->GetMap()->Show();
			}
			//else if(tile.GetOption(OPTION::...)) etc..
		}
	}
}

void Game::ApplyGravity()
{
	Position direction = { 0,1 };
	_currentLevel->GetPlayer()->SetDirection(direction);
	std::vector<Position> playerPositions = _currentLevel->GetPlayer()->GetCollidingPositions();

	if (MovePossible(playerPositions, direction))
	{
		Update(direction);
	}
}

void Game::Update(const Position& direction)
{
	//set player direction
	_currentLevel->GetPlayer()->SetDirection(direction);

	std::vector<EntityTile> oldState = _currentLevel->GetPlayer()->GetBody();
	_currentLevel->GetPlayer()->Update();
	std::vector<EntityTile> newState = _currentLevel->GetPlayer()->GetBody();

	_currentLevel->GetMap()->UpdateMap(oldState, newState);
}

void Game::KeyboardInput(Position& direction)
{
	direction = { 0,0 };

	if (GetAsyncKeyState(VK_UP) and 0x26)
	{
		//up arrow
		direction.y = -1;
	}

	if (GetAsyncKeyState(VK_DOWN) and 0x28)
	{
		//down arrow
		direction.y = 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) and 0x27)
	{
		//right arrow
		direction.x = 1;
	}

	if (GetAsyncKeyState(VK_LEFT) and 0x25)
	{
		//left arrow
		direction.x = -1;
	}
}

void Game::GameLoop()
{
	while (!_currentLevel->GetPlayer()->Dead())
	{
		_timer->Tick();
		
		if (_timer->DeltaTime() >= 1.0f / _frameRate)
		{
			Position direction;
			KeyboardInput(direction);
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
			
			_currentLevel->GetPlayer()->SetDirection(direction);
			std::vector<Position> playerPositions = _currentLevel->GetPlayer()->GetCollidingPositions();

			if (MovePossible(playerPositions, direction)) //if didnt hit any collidables and is in boundings
			{
				Update(direction);
			}

			ApplyGravity();
			CheckOptions();
		}
	}
}

void Game::Start()
{
	if (!SelectionScreen()) // false if exit was selected;
	{
		return;
	}

	Update({ 0,0 });
	_currentLevel->GetMap()->Show();
	GameLoop();
}