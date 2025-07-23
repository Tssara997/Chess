#pragma once
#include <raylib.h>
#include "Piece.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Grid
{
private:
	const size_t size;
	const int cellSize;
	std::vector<std::vector<std::string>> grid;
	bool down;
	int lastColorToMove;
	std::vector<Vector2> kingsPosition;
	std::vector<bool> checkedColor;
	bool checkMate;

	std::vector<std::vector<Piece>>* pieces;
	std::vector<std::vector<Vector2>> avaibleMoves;

	Vector2 position;
	
	void CreateGrid();
	void CreatePieces();
	bool IsMoveAllowed(int, int, int, int) const;
	bool IsPawnMoveAllowed(int, int, int, int) const;
	bool CheckPath(int, int, int, int) const;
	void DrawPath(int, int);
	void ChangePiecePosition(int, int, int, int, std::string idX = "000", std::string idFutureX = "000");
	Piece *GetPiece(std::string id) const;
	bool IsCheck();
	bool IsCheckMate();
	void GetTexture(std::string, int, int) const;
	void AvaibleMoves(int);

public:
	Grid();
	~Grid() {}
	void Draw(); 
	void Update();
};

