#include "Rook.h"

Rook::Rook(int color) : Piece(color, rookId) {
	if (this->color == 0) {
		Image image = LoadImage("AdditonalFiles/castle.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
	else {
		Image image = LoadImage("AdditonalFiles/castleBlack.png");
		ImageResize(&image, 100, 97);
		texture = LoadTextureFromImage(image);
	}
}

bool Rook::Move(int pieceX, int pieceY, int endX, int endY) const {
	return pieceX == endX || pieceY == endY;
}

bool Rook::Attack(int pieceX, int pieceY, int endX, int endY) const {
	return Move(pieceX, pieceY, endX, endY);
}

bool Rook::SpecialMove(int pieceX, int pieceY, int endX, int endY) const {
	return false;
}

void Rook::Draw(int x, int y) const {
	Piece::Draw(x, y);
}

Rook::~Rook() {
	UnloadTexture(texture);
}