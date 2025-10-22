#pragma once

#include "Grid.h"
#include "Button.h"

class Game
{
private:
	bool down;
	Grid grid;
	std::string gameOverText;
	int windowX;
	int windowY;

	Button playAgain;
	Button show;
	Button quit;
	
	void Update();
	void Draw();
	void DrawGameOver() const;
	void Move(int x, int y);
	void Reset();

	typedef enum GameScreen {GAME = 0, GAMEOVER, SHOW} GameScreen;
	GameScreen currentScreen;

public:
	Game(int windowX, int windowY);

	void Run();

	~Game() = default;
};

