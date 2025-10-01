#include "Queen.h"

Queen::Queen(int color) : Piece(color, queenId) {
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/queen.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/queenBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
}

bool Queen::Move(int pieceX, int pieceY, int endX, int endY) const {
	if (pieceX == endX || pieceY == endY)
		return true;
	if (pieceX / endX == 1 && pieceY / endX == 1)
		return true;
	return false;
}

bool Queen::Attack(int pieceX, int pieceY, int endX, int endY) const {
	return Move(pieceX, pieceY, endX, endY);
}

bool Queen::SpecialMove(int pieceX, int pieceY, int endX, int endY) const {
	return false;
}

void Queen::Draw(int x, int y) const {
	Piece::Draw(x, y);
}

Queen::~Queen() {
	UnloadTexture(texture);
}