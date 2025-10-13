#include "Game.h"

Game::Game() : down{ false } {
	Run();
}

void Game::Run() {
	while (!WindowShouldClose()) {
		Update();
		BeginDrawing();
		ClearBackground(BLUE);
		grid.Draw();
		EndDrawing();
	}

	CloseWindow();
}

void Game::Update() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !down && grid.CheckIfCanBeActive(GetMouseX(), GetMouseY())) {
		down = true;
		grid.SetActivePiece(GetMouseX(), GetMouseY());
		grid.PieceAvaibleMoves();
	}
	//else
		//grid.SetActivePiece(-1, -1);
	else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		Move(GetMouseX(), GetMouseY());
		grid.SetActivePiece(-1, -1);
		down = false;
	}
	if (grid.checkMate) {
		while (true) {
			continue;
		}
			
	}
}

void Game::Move(int x, int y) {
	grid.Move(x, y);
}

Game::~Game() {

}

//void Grid::Update() {
//	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !down && !checkMate) {
//		down = true;
//		if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != '0' && grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48 != lastColorToMove) {
//			position.x = (GetMouseX() - GetMouseX() % 100) / 100;
//			position.y = (GetMouseY() - GetMouseY() % 100) / 100;
//		}
//		else
//			position = { -1, -1 };
//	}
//	else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
//		if (down && position.x != -1 && position.y != -1 && 
//			(GetMouseX() - GetMouseX() % 100) / 100 >= 0 && (GetMouseX() - GetMouseX() % 100) / 100 < size &&
//			(GetMouseY() - GetMouseY() % 100) / 100 >= 0 && (GetMouseY() - GetMouseY() % 100) / 100 < size) {
//			if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != grid.at(position.x).at(position.y)[2] &&
//				IsMoveAllowed(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100) &&
//				grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[1] != '6' && 
//				!checkMate)
//			{
//				std::string helperIdX{ grid.at(position.x).at(position.y) };
//				std::string helperIdFutureX{ grid.at((GetMouseY() - GetMouseY() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100) };
//				if (grid.at(position.x).at(position.y)[1] == '6')
//					kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)(GetMouseX() - GetMouseX() % 100) / 100,(float)(GetMouseY() - GetMouseY() % 100) / 100 };
//
//				ChangePiecePosition(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100);
//
//				lastColorToMove = grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48;
//
//				IsCheck();
//				if (IsCheck())
//					IsCheckMate();
//				if (checkedColor.at(lastColorToMove - 1) == 1) {
//					ChangePiecePosition((GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100, position.x, position.y, helperIdX, "000");
//					if (grid.at(position.x).at(position.y)[1] == '6')
//						kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)position.x,(float)position.y };
//					lastColorToMove = (int)(lastColorToMove == 1) + 1;
//				}
//			}
//
//		}
//		position = { -1, -1 };
//		down = false;
//	}
//}