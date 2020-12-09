#include "Game.h"
//for drawing
//void gotoxy(short x, short y)
//{
//	COORD coord = { x,y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

int main()
{
	Game game = Game({ "level1.level", "level2.level" });
	game.Start();

	return 0;
}