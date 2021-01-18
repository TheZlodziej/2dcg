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
		throw new Exception(3, "[LEVEL] (input) level index out of size.");
	}

	std::ifstream levelStream(_levels[_currentLevelIndex]);

	if (levelStream.good())
	{
		_currentLevel = new Level(levelStream);
		_jumpingMaxFrame = _currentLevel->GetPlayer()->GetJumpHeight();
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
	int optionsNumber = 4;
	int levelIndex = _currentLevelIndex;
	bool keyPressed = false;

	auto printSelectionScreen = [&selection, &levelIndex]() {
		std::string backgroundColor = "\u001b[30m\u001b[40m"; // black background, black text
		std::string textColor = "\u001b[37m\u001b[40m"; //white text, black background
		std::string selectedColor = "\u001b[32m\u001b[40m"; //green text, black background
		std::string borderColor = "\u001b[37m\u001b[40m"; //white text, black background
		std::string exitColor = "\u001b[31m\u001b[40m"; //red text, black bakcground
		
		system("cls");

		std::cout << borderColor << "//////////////////////////////////////////////" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................................." << textColor << "Level:" << levelIndex << backgroundColor << ".." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................." << (selection == 0 ? selectedColor + "[Start]" : "." + textColor + "Start" + backgroundColor + ".") << backgroundColor << ".................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "............." << (selection == 1 ? selectedColor + "[Change level]" : "." + textColor + "Change level" + backgroundColor + ".") << backgroundColor << "..............." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "............." << (selection == 2 ? selectedColor + "[How to play?]" : "."+ textColor + "How to play?" + backgroundColor + ".") << backgroundColor << "..............." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................." << (selection == 3 ? exitColor + "[Exit]" : "." + textColor + "Exit" + backgroundColor + ".") << backgroundColor << "..................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//////////////////////////////////////////////" << /* reset colors */ "\u001b[0m" << std::endl;
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
				Sound::Play(Sound::GetSoundFilename(SOUND::SELECT));
				keyPressed = true;
				switch (selection)
				{
				case 0:
					LoadLevel(levelIndex);
					return true;

				case 1:
					levelIndex = (levelIndex + 1) % _levels.size();
					printSelectionScreen();
					break;

				case 2:
					HowToPlayScreen();
					printSelectionScreen();
					break;

				case 3:
					return false;
				}
			}

			if (keyPressed)
			{
				Sound::Play(Sound::GetSoundFilename(SOUND::SELECT));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				keyPressed = false;
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
	for (EntityTile& tile : _currentLevel->GetOptionTiles())
	{
		if (_currentLevel->GetPlayer()->CollidingWith(tile))
		{
			Option option;

			option = tile.GetOption(OPTION::SWITCH_MAP);
			if (option.Good())
			{
				Position newPlayerPosition = Position({ option.arguments[1], option.arguments[2] });
				int newMapIndex = option.arguments[0];
				_currentLevel->LoadMap(newMapIndex);
				_currentLevel->GetPlayer()->SetPosition(newPlayerPosition);
				Update({0,0});
				_currentLevel->GetMap()->Show();
				HUD();
			}

			option = tile.GetOption(OPTION::DEAL_DMG);
			if (option.Good())
			{
				Sound::Play(Sound::GetSoundFilename(SOUND::DEAL_DMG));
				_currentLevel->GetPlayer()->LoseHp(option.arguments[0]);

				if (_currentLevel->GetPlayer()->Dead())
				{
					_currentLevel->End();
				}

				HUD();
			}

			option = tile.GetOption(OPTION::ADD_SCORE);
			if (option.Good())
			{
				int score = option.arguments[0];
				if (score >= 0)
				{
					Sound::Play(Sound::GetSoundFilename(SOUND::ADD_SCORE_G));
				} 
				
				else
				{
					Sound::Play(Sound::GetSoundFilename(SOUND::ADD_SCORE_B));
				}

				_currentLevel->AddScore(score);
				HUD();

				//change to different tile in original map & remove gold option
				char newCharacter = static_cast<char>(option.arguments[1]);
				int newTileColor = option.arguments[2];
				int newBackgroundColor = option.arguments[3];
				_currentLevel->GetMap()->SetCharacterAt(tile.GetPosition(), newCharacter);
				_currentLevel->GetMap()->RemoveOptionAt(tile.GetPosition(), OPTION::ADD_SCORE);
				_currentLevel->GetMap()->SetTileColorAt(tile.GetPosition(), newTileColor);
				_currentLevel->GetMap()->SetTileBackgroundColorAt(tile.GetPosition(), newBackgroundColor);

				_currentLevel->AssignOptionTiles();
			}

			option = tile.GetOption(OPTION::EXIT_LEVEL);
			if (option.Good())
			{
				_currentLevel->End();
			}
		}
	}
}

void Game::ApplyGravity()
{
	//check if a block below player {or any gravity-object} is collidable then move down if isn't
	Position direction = { 0,1 };
	_currentLevel->GetPlayer()->SetDirection(direction);
	std::vector<Position> playerPositions = _currentLevel->GetPlayer()->GetCollidingPositions();

	if (MovePossible(playerPositions, direction))
	{
		Update(direction);
		if (!_playerJumping) //prevents jumping after started falling
		{
			_playerJumping = true;
			_jumpingFrame = _jumpingMaxFrame + 1;
		}
	}
	else
	{
		_playerJumping = false;
		_jumpingFrame = 0;
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
		if (!_playerJumping)
		{
			_playerJumping = true;
			Sound::Play(Sound::GetSoundFilename(SOUND::JUMP));
		}
	}

	if (GetAsyncKeyState(VK_DOWN) and 0x28)
	{
		//down arrow
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

void Game::Jump()
{
	if (_playerJumping)
	{
		_jumpingFrame++;
		std::vector<Position> playerPositions = _currentLevel->GetPlayer()->GetCollidingPositions();

		if (_jumpingFrame < _jumpingMaxFrame)
		{
			Position topLeft = _currentLevel->GetPlayer()->TopLeft() + Position({0, -2});
			Position bottomRight = _currentLevel->GetPlayer()->BottomRight() + Position({0, -2});
			if (MovePossible(playerPositions, { 0, -1 }) and _currentLevel->GetMap()->InBoundings(topLeft) and _currentLevel->GetMap()->InBoundings(bottomRight))
			{
				//gravity forces 1 down so you need to go 2 up
				_currentLevel->GetPlayer()->SetDirection({ 0, -2 });
				Update({ 0,-2 }); 
			}
			else
			{
				//end jumping
				_jumpingFrame = _jumpingMaxFrame;
				//make it look more realistic
				_currentLevel->GetPlayer()->SetDirection({ 0,-1 });
				Update({ 0,-1 }); 
			}
		}
		
		else if (_jumpingFrame == _jumpingMaxFrame) //hung in the air on the last frame so it looks more realistic
		{
			if (MovePossible(playerPositions, { 0, -1 }))
			{
				_currentLevel->GetPlayer()->SetDirection({ 0,-1 });
				Update({ 0,-1 });
			}
		}
	}
} 

void Game::Move(const Position& direction)
{
	if (direction != Position{ 0, 0 })
	{
		std::vector<Position> playerPositions = _currentLevel->GetPlayer()->GetCollidingPositions();

		if (MovePossible(playerPositions, direction))
		{
			_currentLevel->GetPlayer()->SetDirection(direction);
			Update(direction);
		}
	}
}

void Game::LostScreen()
{
	int selection = 0; // selection: 0=restart; 1=quit
	int optionsNumber = 3;
	bool keyPressed = false;
	bool selected = false;
	
	//displaying
	auto printGameOverScreen = [&selection]() {
		std::string backgroundColor = "\u001b[30m\u001b[40m"; // black background, black text
		std::string textColor = "\u001b[37m\u001b[40m"; //white text, black background
		std::string selectedColor = "\u001b[32m\u001b[40m"; //green text, black background
		std::string borderColor = "\u001b[37m\u001b[40m"; //white text, black background
		std::string gameoverColor = "\u001b[31m\u001b[40m"; //red text, black bakcground
		std::string exitColor = "\u001b[31m\u001b[40m"; //red text, black bakcground

		system("cls");

		std::cout << borderColor << "///////////////////////////////////////////////" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................."<< gameoverColor  << "Game Over" << backgroundColor << "................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................." << (selection == 0 ? selectedColor + "[Restart]" : "." + textColor + "Restart" + backgroundColor + ".") << backgroundColor << "................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".............." << (selection == 1 ? selectedColor + "[Start Screen]" : "." + textColor + "Start Screen" + backgroundColor + ".") << backgroundColor << "..............." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................." << (selection == 2 ? exitColor + "[Exit]" : "." + textColor + "Exit" + backgroundColor + ".") << backgroundColor << "..................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "///////////////////////////////////////////////" << /* reset colors */ "\u001b[0m" << std::endl;
	};

	printGameOverScreen();
	while (!selected)
	{
		_timer->Tick();
		if (_timer->DeltaTime() >= 1.0f / _frameRate)
		{
			// up arrow
			if (GetAsyncKeyState(VK_UP) and 0x26)
			{
				keyPressed = true;
				selection = ((selection - 1) % optionsNumber) < 0 ? optionsNumber - 1 : selection - 1;
				printGameOverScreen();
			}

			// down arrow
			else if (GetAsyncKeyState(VK_DOWN) and 0x28)
			{
				keyPressed = true;
				selection = (selection + 1) % optionsNumber;
				printGameOverScreen();
			}

			// enter
			else if (GetAsyncKeyState(VK_RETURN) and 0x0D)
			{
				Sound::Play(Sound::GetSoundFilename(SOUND::SELECT));
				selected = true;
			}

			if (keyPressed)
			{
				Sound::Play(Sound::GetSoundFilename(SOUND::SELECT));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				keyPressed = false;
			}
		}
	}

	if (selection == 0)
	{
		RestartLevel();
	}
	else if (selection == 1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // to prevent accidental game start
		Start();
	}
	else if (selection == 2)
	{
		return;
	}
}

void Game::GameLoop()
{
	while (!_currentLevel->Ended())
	{
		_timer->Tick();
		
		if (_timer->DeltaTime() >= 1.0f / _frameRate)
		{
			Position direction;
			KeyboardInput(direction);
			Jump();
			Move(direction);
			CheckOptions();
			ApplyGravity();
			std::this_thread::sleep_for(std::chrono::milliseconds(35));
		}
	}

	if (_currentLevel->GetPlayer()->Dead())
	{
		Sound::Play(Sound::GetSoundFilename(SOUND::LOSE));
		LostScreen();
	}
	else
	{
		if (_currentLevel->GetScore() > _currentLevel->GetHighscore())
		{
			std::fstream levelStream;
			levelStream.open(_levels[_currentLevelIndex], std::ios::in | std::ios::out);
			if (levelStream.good())
			{
				_currentLevel->SetHighscore(levelStream);
			}
			
			else
			{
				throw new Exception(1, "[LEVEL] (output) file open error");
			}
			
			levelStream.close();
		}
		
		Sound::Play(Sound::GetSoundFilename(SOUND::WIN));
		WonScreen();
	}
}

void Game::HUD()
{
	std::string textColor = "\u001b[37m\u001b[40m"; //white text, black background
	std::string backgroundColor = "\u001b[30m\u001b[40m"; //black text, black bakcground
	std::string heartsColor = "\u001b[31m\u001b[40m"; //red text, black background
	std::string scoreColor = "\u001b[33m\u001b[40m"; //yellow text, black bakcground

	int mapHeight = _currentLevel->GetMap()->GetHeight();
	int mapWidth = _currentLevel->GetMap()->GetWidth();
	int maxHp = _currentLevel->GetPlayer()->MaxHp();
	int Hp = _currentLevel->GetPlayer()->Hp();
	int score = _currentLevel->GetScore();
	int highscore = _currentLevel->GetHighscore();

	//clear HUD
	Map::GotoPosition({ 0, mapHeight + 1 });

	for (int i = 0; i < mapWidth + 2 * maxHp; i++)
	{
		std::cout << backgroundColor << ".";
	}

	//draw new HUD data
	Map::GotoPosition({ 0, mapHeight + 1 });

	//score
	std::cout << textColor << "Score:" << backgroundColor << "." << scoreColor << score << backgroundColor << ".";

	//hearts
	for (int i = 0; i < mapWidth - 2 * maxHp - 7 /* Hearts: - 7 chars */- 7 /* Score: - 7 chars */ - Digits(score) - 1 /* 1 minimum space char */; i++)
	{
		std::cout << backgroundColor << ".";
	}

	std::cout << textColor << "Hearts:"; //red color
	for (int i = 0; i < Hp; i++)
	{
		std::cout << backgroundColor << "." << heartsColor << "*";
	}
	std::cout << textColor;
	for (int i = 0; i < maxHp - Hp; i++)
	{
		std::cout << backgroundColor << "." << textColor << "_";
	}

	//highscore
	std::cout << textColor << "\n\nHighscore:" << scoreColor << ((score > highscore) ? score : highscore);

	//level info
	std::cout << textColor << "\n\nLevel: (" << _currentLevelIndex << ") [" << _levels[_currentLevelIndex] << "]";
}

void Game::RestartLevel()
{
	Update({ 0,0 });
	LoadLevel(_currentLevelIndex);
	_currentLevel->GetMap()->Show();
	HUD();
	GameLoop();
}

void Game::Start()
{
	if (!SelectionScreen()) // false if exit was selected;
	{
		return;
	}

	RestartLevel();
}

void Game::HowToPlayScreen()
{
	std::string backgroundColor = "\u001b[30m\u001b[40m"; // black background, black text
	std::string textColor = "\u001b[37m\u001b[40m"; //white text, black background
	std::string borderColor = "\u001b[37m\u001b[40m"; //white text, black background
	std::string highlightColor = "\u001b[36m\u001b[40m"; //cyan text, black background

	for (int i = 15; i > 0; i--)
	{
		system("cls");

		std::cout << borderColor << "//////////////////////////////////////////////////////" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "................." << textColor << "Welcome to " << highlightColor << "2dcg!" << backgroundColor << "................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "............" << textColor << "Use arrow buttons to navigate" << backgroundColor << "........." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..................." << textColor << "around the map" << backgroundColor << "................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "............" << textColor << "There are some special blocks" << backgroundColor << "........." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "........." << textColor << "that may damage your, give you gold" << backgroundColor << "......" << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "........" << textColor << "or even teleport you to another room" << backgroundColor << "......" << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..............." << textColor << "You will be redirected" << backgroundColor << "............." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".............." << textColor << "to the main screen in: " << highlightColor << i << ( i >= 10 ? "" : backgroundColor + "." ) << backgroundColor << "..........." << borderColor << "//" << std::endl; //11,41
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//////////////////////////////////////////////////////" << /* reset colors */ "\u001b[0m" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Game::WonScreen()
{
	std::string backgroundColor = "\u001b[30m\u001b[40m"; // black background, black text
	std::string textColor = "\u001b[37m\u001b[40m"; //white text, black background
	std::string borderColor = "\u001b[37m\u001b[40m"; //white text, black background
	std::string highlightColor = "\u001b[36m\u001b[40m"; //cyan text, black background
	std::string scoreColor = "\u001b[33m\u001b[40m"; //yellow text, black background

	for (int i=15; i>0; i--)
	{
		system("cls");
		std::cout << borderColor << "///////////////////////////////////////////////" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".................." << highlightColor << "You Won!" << backgroundColor << "................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl; 
		
		//gold
		int score = _currentLevel->GetScore();

		std::cout << borderColor << "//" << backgroundColor << ".............." << textColor << "Your Score: " << scoreColor << score << backgroundColor;
		
		for (int i = 0; i < 18 - Digits(score); i++) 
		{ 
			std::cout << "."; 
		} 

		std::cout << borderColor << "//" << std::endl; 
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........." << textColor << "You will be redirected" << backgroundColor << ".........." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << ".........." << textColor << "to the start screen in "<< highlightColor << i << backgroundColor << (i>=10 ? "" : "." )<<"........" << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "//" << backgroundColor << "..........................................." << borderColor << "//" << std::endl;
		std::cout << borderColor << "///////////////////////////////////////////////" << /* reset colors */ "\u001b[0m" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	Start();
}

int Game::Digits(int number)
{
	int numberOfDigits = 1;

	if (number < 0)
	{
		number = -number;
		numberOfDigits++;
	}

	while (number > 0)
	{
		number /= 10;
		numberOfDigits++;
	}

	return numberOfDigits;
}