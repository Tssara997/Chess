#pragma once

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Position.h"


#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <raylib.h>

class Grid
{
private:
	// const values
	static constexpr size_t defSize = 8;
	static constexpr int defCellSize = 100;

	// New
	const size_t size;
	const int cellSize;
	std::vector<std::vector<std::string>> grid;
	std::vector<std::vector<Piece*>> pieces;
	Position activePiecePos;

	// Old
	bool down;
	int lastColorToMove;
	std::vector<Vector2> kingsPosition;
	std::vector<bool> checkedColor;
	bool checkMate;
	std::vector<std::vector<Vector2>> avaibleMoves;

	Vector2 position;
	
	// New
	void CreateGrid();
	void CreatePieces();
	void DrawActivePiece() const;
	//bool IsMoveAllowed(int, int, int, int) const;
	//bool IsPawnMoveAllowed(int, int, int, int) const;
	//bool CheckPath(int, int, int, int) const;
	//void DrawPath(int, int);
	//void ChangePiecePosition(int, int, int, int, std::string idX = "000", std::string idFutureX = "000");
	//Piece *GetPiece(std::string id) const;
	//bool IsCheck();
	//bool IsCheckMate();
	//void GetTexture(std::string, int, int) const;
	//void AvaibleMoves(int);

public:
	Grid();
	~Grid() {}
	void Draw() const; 
	bool OutOfBanceCheck(const Position& pos) const;
	bool IsSquareAvaible(const Position& pos) const;
	bool CanAttack(const Position& pos) const;
	bool IsMoveAllowed(const Position& posStart, const Position& posEnd) const;
	void SetActivePiece(int x, int y);
	bool CheckIfCanBeActive(int x, int y);
	Position CreatePosition(int x, int y);
	void Move(int x, int y);
	//void Update();
};

