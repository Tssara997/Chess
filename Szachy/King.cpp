#include "King.h"

King::King(int color) : Piece(color, kingId) {
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/king.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/kingBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
}

bool King::Move(int pieceX, int pieceY, int endX, int endY) const {
	if ((pieceX == endX && abs(pieceY - endY) == 1) || 
		(abs(pieceX - endX) == 1 && pieceY == endY))
		return true;
	return false;
}

bool King::Attack(int pieceX, int pieceY, int endX, int endY) const {
	return Move(pieceX, pieceY, endX, endY);
}

bool King::SpecialMove(int pieceX, int pieceY, int endX, int endY) const {
	if (pieceX == endX || pieceY == endY)
		return true;

	if (pieceX / endX == 1 && pieceY / endY == 1)
		return true;

	if ((abs(pieceX - endX) == 1 && abs(pieceY - endY) == 2) ||
		(abs(pieceX - endX) == 2 && abs(pieceY == endY) == 1))
		return true;

	return false;
}

void King::Draw(int x, int y) const {
	Piece::Draw(x, y);
}

King::~King() {
	UnloadTexture(texture);
}