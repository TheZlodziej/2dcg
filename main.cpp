#include "Game.h"

int main()
{
	try
	{
		Game game = Game({ "levels/level2.level", "levels/level1.level" });
		game.Start();
	}
	catch (Exception* exception)
	{
		exception->Display();
		delete exception;
	}
	catch (...)
	{
		Exception::Unknown();
	}

	return 0;
}