#include "Knight.h"

Knight::Knight(int color) : Piece(color, knightId) {
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/knight.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/knightBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
}

bool Knight::Move(int pieceX, int pieceY, int endX, int endY) const {
	if ((abs(pieceX - endX) == 1 && abs(pieceY - endY) == 1) ||
		(abs(pieceX - endX) == 2 && abs(pieceY - endY == 2)))
		return true;
	return false;
}

bool Knight::Attack(int pieceX, int pieceY, int endX, int endY) const {
	return Move(pieceX, pieceY, endX, endY);
}

bool Knight::SpecialMove(int pieceX, int pieceY, int endX, int endY) const {
	return false;
}

void Knight::Draw(int x, int y) const {
	Piece::Draw(x, y);
}


Knight::~Knight() {
	UnloadTexture(texture);
}