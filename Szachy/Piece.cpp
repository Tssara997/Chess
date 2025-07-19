#include "Piece.h"
#include <iostream>

Pawn::Pawn(int color)
{
	this->color = color;
	id = 1;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/pawn.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/pawnBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	if (this->color == 2) {
		allowedMoves = { {0,1} };
		specialAllowedMoves = { {0,2} };
		attakMoves = { {-1,1}, {1, 1} };
	}
	else if (this->color == 1) {
		allowedMoves = { {0,-1} };
		specialAllowedMoves = { {0,-2} };
		attakMoves = { {-1,-1}, {1, -1} };
	}
}

Knight::Knight(int color)
{
	this->color = color;
	id = 2;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/knight.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/knightBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}

	allowedMoves = {{2,1}, {1, 2}, {-2,-1}, {-1, -2} , {-2,1}, {-1, 2} , {2,-1}, {1, -2}};
}

Bishop::Bishop(int color)
{
	this->color = color;
	id = 3;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/bishop.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/bishopBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}

	allowedMoves = {};

	for (float i{ 1 }; i < 9; ++i)
		for (float j{ -1 }; j <= 1; j += 2) {
			allowedMoves.push_back({ i * j, i * j});
			allowedMoves.push_back({ i * j, i * j * -1 });
		}
}

Rook::Rook(int color)
{
	this->color = color;
	id = 4;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/castle.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/castleBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}

	allowedMoves = {};

	for (float i{ 1 }; i < 9; ++i)
		for (float j{ -1 }; j <= 1; j += 2) {
			allowedMoves.push_back({ i * j, 0 });
			allowedMoves.push_back({ 0, i * j});
		}
}

Queen::Queen(int color)
{
	this->color = color;
	id = 5;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/queen.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/queenBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}

	allowedMoves = {};
	for (float i{ 1 }; i < 9; ++i) 
		for (float j{ -1 }; j <= 1; j += 2) {
			allowedMoves.push_back({ i * j, i * j });
			allowedMoves.push_back({ i * j, i * j * -1 });
			allowedMoves.push_back({ 0, i * j });
			allowedMoves.push_back({ i*j, 0 });
		}
}

King::King(int color)
{
	this->color = color;
	id = 6;
	if (color == 1) {
		Image image = LoadImage("AdditonalFiles/king.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/kingBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}

	allowedMoves = { {0, 1}, {1,1}, {1, 0}, {0, -1}, {-1,-1}, {-1, 0}, {1,-1}, {-1,1} };
	checkPositions = { {2,1}, {1, 2}, {-2,-1}, {-1, -2} , {-2,1}, {-1, 2} , {2,-1}, {1, -2} };
	for (float i{ 1 }; i < 9; ++i)
		for (float j{ -1 }; j <= 1; j += 2) {
			checkPositions.push_back({ i * j, i * j });
			checkPositions.push_back({ i * j, i * j * -1 });
			checkPositions.push_back({ 0, i * j });
			checkPositions.push_back({ i * j, 0 });
		}

}
