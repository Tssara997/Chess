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
	static constexpr Color defCircleColor = { 133,133,133,200 };
	static constexpr Color defRectangleColor = { 220, 20 ,60, 100 };
	static constexpr float defCircleRadius = 20;
	static constexpr bool defCheckmate = false;
	static constexpr int defColorToMove = 0;

	// New
	const size_t size;
	const int cellSize;
	const Color circleColor;
	const Color rectangleColor;
	const float circleRadius;

	std::vector<std::vector<std::string>> grid;
	std::vector<std::vector<Piece*>> pieces;
	Position* activePiecePos;
	bool checkMate;
	std::vector<Vector2> kingsPosition;
	int colorToMove;

	// Old
	std::vector<bool> checkedColor;
	std::vector<std::vector<Vector2>> avaibleMoves;

	Vector2 position;

	// New
	void CreateGrid();
	void CreatePieces();
	void DrawActivePiece() const;
	bool IsPieceActive() const;
	bool IsMoveAllowed(const Position& pos) const;
	bool OutOfBanceCheck(int x, int y) const;
	bool IsAttackAllowed(const Position& pos, const Position* activePiecePos = new Position{}) const;
	bool IsPieceJumping(const Position& pos, const Position* activePiecePos = new Position{}) const;
	void DrawPieceAvaibleMoves() const;
	Position CreatePositionFromGrid(int x, int y) const;
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
	~Grid() { delete activePiecePos; }
	void Draw() const;
	bool IsSquareAvaible(const Position& pos) const;
	bool CanAttack(const Position& pos) const;
	void SetActivePiece(int x, int y);
	bool CheckIfCanBeActive(int x, int y);
	Position CreatePositionFromScreen(int x, int y) const;
	bool CheckIfCheck(const Position& pos = Position{}) const;
	void Move(int x, int y);
	//void Update();
};

