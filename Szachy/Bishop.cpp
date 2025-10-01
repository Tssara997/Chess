#include "Bishop.h"

Bishop::Bishop(int color) : Piece(color, bishopId) {
	id = bishopId;
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/bishop.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/bishopBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
}

bool Bishop::Move(int pieceX, int pieceY, int endX, int endY) const {
	return pieceX / endX == 1 && pieceY / endY == 1;
}

bool Bishop::Attack(int pieceX, int pieceY, int endX, int endY) const {
	return Move(pieceX, pieceY, endX, endY);
}

bool Bishop::SpecialMove(int pieceX, int pieceY, int endX, int endY) const {
	return false;
}

void Bishop::Draw(int x, int y) const {
	Piece::Draw(x, y);
}

Bishop::~Bishop() {
	UnloadTexture(texture);
}