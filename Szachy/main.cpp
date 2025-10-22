#include "Game.h"


int main()
{
	int windowX{ 800 }, windowY{ 800 };
	InitWindow(windowX, windowY, "Chess");
	SetTargetFPS(60);
	Game game{ windowX, windowY };

	return 0;
}