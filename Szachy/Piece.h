#pragma once
#include <raylib.h>
#include <cmath>
#include <vector>

class Piece
{
private:

public:
	int id{ 0 };
	int color;
	Texture2D texture;
	std::vector<Vector2> allowedMoves;
	std::vector<Vector2> specialAllowedMoves{};
	std::vector<Vector2> attakMoves{};
	std::vector<Vector2> checkPositions{};
};

class Pawn : public Piece
{
public:
	Pawn(int color);
};

class Knight : public Piece
{
public:
	Knight(int color);
};

class Bishop : public Piece
{
public:
	Bishop(int color);
};

class Rook : public Piece
{
public:
	Rook(int color);
};

class Queen : public Piece
{
public:
	Queen(int color);
};

class King : public Piece
{
public:
	King(int color);
};