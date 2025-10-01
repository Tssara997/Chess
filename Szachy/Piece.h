#pragma once

#include <raylib.h>
#include <iostream>
#include <cmath>

class Piece
{
protected:
	int id;
	int color;
	Texture2D texture;

public:
	Piece(int color, int id);
	virtual bool Move(int pieceX, int pieceY, int endX, int endY) const = 0;
	virtual bool Attack(int pieceX, int pieceY, int endX, int endY) const = 0;
	virtual bool SpecialMove(int pieceX, int pieceY, int endX, int endY) const = 0;
	virtual void Draw(int x, int y) const = 0;
	virtual ~Piece() {}
};