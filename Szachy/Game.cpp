#include "Game.h"

Game::Game(int windowX, int windowY) : down{ false }, currentScreen{ GAME }, gameOverText{ }, windowX{ windowX }, windowY{ windowY } {

	playAgain = Button{ "Play Again", -1, 300, windowX, windowY };
	show = Button{ "Show Board", -1, 400, windowX, windowY };
	quit = Button{ "Exit", -1, 500, windowX, windowY };
	Run();
}

void Game::Run() {
	while (!WindowShouldClose()) {
		Draw();
	}

	CloseWindow();
}

void Game::Draw() {
	switch (currentScreen) {
	case GAME:
		Update();
		if (grid.IsGameOver())
			currentScreen = GAMEOVER;
		break;
	case GAMEOVER:
		if (grid.CanColorMove(1))
			gameOverText = "White Won!";
		else
			gameOverText = "Black Won!";
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (playAgain.CheckIfClicked(GetMouseX(), GetMouseY())) {
				currentScreen = GAME;
				Reset();
			} 
			if (show.CheckIfClicked(GetMouseX(), GetMouseY()))
				currentScreen = SHOW;
			if (quit.CheckIfClicked(GetMouseX(), GetMouseY()))
				exit(0);
		}
		break;
	case SHOW:
		if (IsKeyPressed(KEY_ENTER)) {
			currentScreen = GAME;
			Reset();
		}
		break;
	default:
		break;
	}

	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	switch (currentScreen) {
	case GAME:
		grid.Draw();
		break;
	case GAMEOVER:
		DrawGameOver();
		break;
	case SHOW:
		grid.Draw();
		break;
	default: 
		break;
	}
	EndDrawing();
}

void Game::DrawGameOver() const {
	DrawText(gameOverText.c_str(), (windowX - MeasureText(gameOverText.c_str(), 70)) / 2, 70, 70, BLACK);
	playAgain.Draw();
	show.Draw();
	quit.Draw();
}

void Game::Update() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !down && grid.CheckIfCanBeActive(GetMouseX(), GetMouseY())) {
		grid.SetActivePiece(GetMouseX(), GetMouseY());
		if (grid.CanColorMove()) {
			down = true;
			grid.PieceAvaibleMoves();
		}
		else {
			grid.SetActivePiece(-1, -1);
		}
	}
	else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		Move(GetMouseX(), GetMouseY());
		grid.SetActivePiece(-1, -1);
		down = false;
	}
}

void Game::Move(int x, int y) {
	grid.Move(x, y);
}

void Game::Reset() {
	grid.Reset();
}