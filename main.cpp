#include "Game.h"

int main()
{
	try 
	{
		Game game = Game({ "levels/level1.level", "levels/level2.level" });
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