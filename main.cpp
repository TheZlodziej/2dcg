#include "Level.h"
#include "Player.h"
#include <Windows.h>

//for drawing
//void gotoxy(short x, short y)
//{
//	COORD coord = { x,y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

int main()
{
	Level* level = new Level("level1.level");
	level->Show();

	delete level;

	//EntityTile t = EntityTile('o', true, { 0,0 });
	//Entity* entity = new Entity({ t });
	////Map m = Map("map1.map");

	return 0;
}