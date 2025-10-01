#include "Piece.h"

Piece::Piece(int color, int id) : color{ color }, id{id}, texture{} {

}

void Piece::Draw(int x, int y) const {
	DrawTexture(texture, x, y, WHITE);
}
