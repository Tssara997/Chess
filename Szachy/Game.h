#pragma once

#include "Grid.h"

class Game
{
private:
	bool down;
	Grid grid;
	
	void Update();
	void Move(int x, int y);

public:
	Game();

	void Run();

	~Game();
};

