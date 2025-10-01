#include "Pawn.h"

Pawn::Pawn(int color) : Piece{color, pawnId}
{
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/pawn.png");
		ImageResize(&image, 100, 97);
		this->texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
	else {
		Image image = LoadImage("C:/Users/majab/source/repos/Chess/Szachy/AdditonalFiles/pawnBlack.png");
		ImageResize(&image, 100, 97);
		this->texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
}

bool Pawn::Move(int pieceX, int pieceY, int endX, int endY) const
{
	if (color == 0)
		return pieceX == endX && pieceY - endY == 1;
	return pieceX == endX && pieceY - endY == -1;
}

bool Pawn::Attack(int pieceX, int pieceY, int endX, int endY) const
{
	if (color == 0)
		return abs(pieceX - endX) == 1 && pieceY - endY == 1;
	return abs(pieceX - endX) == 1 && pieceY - endY == -1;
}

bool Pawn::SpecialMove(int pieceX, int pieceY, int endX, int endY) const
{
	if (pieceY != 6 && pieceY != 1)
		return false;
	if (color == 0)
		return pieceX == endX && pieceY - endY == 2;
	return pieceX == endX && pieceY - endY == -2;
}

void Pawn::Draw(int x, int y) const {
	Piece::Draw(x, y);
}

Pawn::~Pawn() {
	
	//UnloadTexture(texture);
}