#include <iostream>
#include <raylib.h>
#include "Grid.h"

int main()
{
	InitWindow(800, 800, "Chess");
	SetTargetFPS(60);

	Grid grid;

	while (!WindowShouldClose()) {
		grid.Update();
		BeginDrawing();
		ClearBackground(BLUE);
		grid.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}