#include "Game.h"

int main()
{
	try 
	{
		Game game = Game({ "level1.level", "level2.level" });
		game.Start();
	}
	catch (Exception* exception)
	{
		exception->Display();
		delete exception;
	}

	return 0;
}