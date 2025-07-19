#include "Grid.h"
#include <iostream>

Grid::Grid() : size{ 8 }, cellSize{ 100 }, grid{}, down{ false }, position{ -1, -1 }, lastColorToMove{2}, checkedColor{0,0}, isThereAnyMoves{false}, checkMate{false}
{
	kingsPosition = { {4,7},{4,0} };
	pieces = new std::vector<std::vector<Piece>>;
	CreatePieces();
	CreateGrid();
}

void Grid::CreatePieces() {
	pieces->push_back({ Pawn{1}, Pawn{2} });
	pieces->push_back({ Knight{1}, Knight{2} });
	pieces->push_back({ Bishop{1}, Bishop{2} });
	pieces->push_back({ Rook{1}, Rook{2} });
	pieces->push_back({ Queen{1}, Queen{2} });
	pieces->push_back({ King{1}, King{2} });
}

Piece *Grid::GetPiece(std::string id) const {
	int pieceId = id[1] - 49;
	int colorId = id[2] - 49;
	if(pieceId >= 0 && pieceId <= 5)
		return &pieces->at(pieceId).at(colorId);
	return NULL;
}

void Grid::CreateGrid()
{
	std::fstream chessBoard("AdditonalFiles/chessBoard.txt");
	std::string line;
	int i{1};
	std::vector<std::string> pomoc;
	while (std::getline(chessBoard, line)) {
		pomoc.push_back(line);
		if (i % size == 0 && i != 0) {
			grid.push_back(pomoc);
			pomoc.clear();
		}
		++i;
	}

	chessBoard.close();
}

void Grid::GetTexture(std::string id, int x, int y) const {
	auto piece = GetPiece(id);
	if (piece != NULL)
		DrawTexture(piece->texture, x, y, WHITE);
}

void Grid::Draw(){
	Texture2D ct{};
	for (int i{}; i < size; ++i)
		for (int j{}; j < size; ++j) {
			if (grid.at(i).at(j)[0] == '1')
				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, LIGHTGRAY);
			else
				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, DARKGREEN);

			if ((position.x != i || position.y != j) && grid.at(i).at(j)[1] != '0') {
				GetTexture(grid.at(i).at(j), i * cellSize, j * cellSize);
			}
		}

	if (position.x != -1 && position.y != -1) {
		DrawPath(position.x, position.y);
		GetTexture(grid.at(position.x).at(position.y), GetMouseX() - cellSize / 2, GetMouseY() - cellSize / 2);
	}
}

void Grid::DrawPath(int x, int y){
	std:: string helperIdX{}, helperIdFutureX;
	bool check{ false };
	double radius{ 20 };
	const auto piece = GetPiece(grid.at(x).at(y));
	for (const auto& position : piece->allowedMoves) {
		if (position.x + x < size && position.x + x >= 0 && position.y + y < size && position.y + y >= 0 && grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color){
			helperIdX = grid.at(x).at(y);
			helperIdFutureX = grid.at(x + position.x).at(y + position.y);
			ChangePiecePosition(x, y, x + position.x, y + position.y);
			IsCheck();
			check = checkedColor.at(piece->color - 1) == 1;
			ChangePiecePosition(x + position.x, y + position.y, x, y, helperIdX, helperIdFutureX);
			if (piece->id == 2) {
				if (!check) {
					if (grid.at(x + position.x).at(y + position.y)[2] == '0') {
						DrawCircle(((x + position.x) * cellSize + cellSize / 2), ((y + position.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
					}
					else if (grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color && grid.at(x + position.x).at(y + position.y)[1] != '6') {
						DrawRectangle((x + position.x) * cellSize, (y + position.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
					}
				}
				
			}
			
			if (piece->id == 1) {
				if (grid.at(x + position.x).at(y + position.y)[2] == '0' && !check)
					DrawCircle(((x + position.x) * cellSize + cellSize / 2), ((y + position.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
				for (const auto& attackMove : piece->attakMoves)
					if (x + attackMove.x >= 0 && x + attackMove.x < 8 && y + attackMove.y + y >= 0 && y + attackMove.y < 8) {
						helperIdX = grid.at(x).at(y);
						helperIdFutureX = grid.at(x + attackMove.x).at(y + attackMove.y);
						ChangePiecePosition(x, y, x + attackMove.x, y + attackMove.y);
						IsCheck();
						check = checkedColor.at(piece->color - 1) == 1;
						ChangePiecePosition(x + attackMove.x, y + attackMove.y, x, y, helperIdX, helperIdFutureX);
						if (grid.at(x + attackMove.x).at(y + attackMove.y)[2] - 48 != piece->color && grid.at(x + attackMove.x).at(y + attackMove.y)[2] != '0') {
							/*helperIdX = grid.at(x).at(y);
							helperIdFutureX = grid.at(x + attackMove.x).at(y + attackMove.y);
							ChangePiecePosition(x, y, x + attackMove.x, y + attackMove.y);
							IsCheck();
							check = checkedColor.at(piece->color - 1) == 1;
							ChangePiecePosition(x + attackMove.x, y + attackMove.y, x, y, helperIdX, helperIdFutureX);*/
							if (!check) {
								DrawRectangle((x + attackMove.x) * cellSize, (y + attackMove.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
							}
								
						}
					}
				if ((y == 1 || y == 6)) {
					if (grid.at(x + piece->specialAllowedMoves.at(0).x).at(y + piece->specialAllowedMoves.at(0).y)[2] == '0' && CheckPath(x, y, x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y)) {
						helperIdX = grid.at(x).at(y);
						helperIdFutureX = grid.at(x + piece->specialAllowedMoves.at(0).x).at(y + piece->specialAllowedMoves.at(0).y);
						ChangePiecePosition(x, y, x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y);
						IsCheck();
						check = checkedColor.at(piece->color - 1) == 1;
						ChangePiecePosition(x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y, x, y, helperIdX, helperIdFutureX);
						if (!check) {
							DrawCircle(((x + piece->specialAllowedMoves.at(0).x) * cellSize + cellSize / 2), ((y + piece->specialAllowedMoves.at(0).y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
						}
					}
				}
			}

			else if (piece->id == 6) {
				if (grid.at(x + position.x).at(y + position.y)[2] - 48 == piece->color)
					continue;
				else {
					Vector2 helperPosition = kingsPosition.at(piece->color - 1);
					kingsPosition.at(piece->color - 1) = { x + position.x, y + position.y };
					helperIdX = grid.at(x).at(y);
					helperIdFutureX = grid.at(x + position.x).at(y + position.y);
					ChangePiecePosition(x, y, x + position.x, y + position.y);
					IsCheck();
					ChangePiecePosition(x + position.x, y + position.y, x, y, helperIdX, helperIdFutureX);
					kingsPosition.at(piece->color - 1) = helperPosition;
					check = checkedColor.at(piece->color - 1) == 1;
					if (!check) {
						if (grid.at(x + position.x).at(y + position.y)[2] == '0') {
							DrawCircle(((x + position.x) * cellSize + cellSize / 2), ((y + position.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
						}
						else if (grid.at(x + position.x).at(y + position.y)[2] != piece->color) {
							DrawRectangle((x + position.x) * cellSize, (y + position.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
						}	
					}	
				}	
			}

			else if (CheckPath(x, y, position.x + x, position.y + y)) {
				if (!check) {
					if (grid.at(position.x + x).at(position.y + y)[2] == '0'){
						DrawCircle(((x + position.x) * cellSize + cellSize / 2), ((y + position.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
					}
					else if (grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color && grid.at(x + position.x).at(y + position.y)[1] != '6') {
						DrawRectangle((x + position.x) * cellSize, (y + position.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
					}
				}
			}
		}
	}
}

bool Grid::CheckPath(int x, int y, int futureX, int futureY) const {
	if (grid.at(x).at(y)[1] == '2')
		return grid.at(futureX).at(futureY)[2] != grid.at(x).at(y)[2];
	int moveX{ x != futureX };
	int moveY{ y != futureY };
	int i{ 1 };
	if (x > futureX)
		moveX = -1;
	else if (x < futureX)
		moveX = 1;
	if (y > futureY)
		moveY = -1;
	else if (y < futureY)
		moveY = 1;

	while (x + i * moveX != futureX || y + i * moveY != futureY) {
		if (grid.at(x + i * moveX).at(y + i * moveY)[2] != '0')
			return false;
		i++;
	}

	return true;
}

bool Grid::IsMoveAllowed(int x, int y, int futureX, int futureY) const {
	bool allowed = false;
	const auto piece = GetPiece(grid.at(x).at(y));
	Vector2 move = { abs(x - futureX), abs(y - futureY) };
	if (piece != NULL) {
		if (piece->id == 1)
			return IsPawnMoveAllowed(x, y, futureX, futureY);
		else {
			for (const auto& position : piece->allowedMoves) {
				if (position.x == move.x && position.y == move.y) {
					allowed = true;
					break;
				}

			}
			if (allowed && piece->id != 2)
				return CheckPath(x, y, futureX, futureY);
		}
	}
	return allowed;
}

bool Grid::IsPawnMoveAllowed(int x, int y, int futureX, int futureY) const
{
	std::string id = grid.at(x).at(y);
	const auto piece = pieces->at(0).at(id[2] - 49);
	Vector2 move = { futureX - x, futureY - y };
	if ((grid.at(futureX).at(futureY)[2] - 48 != (&piece)->color == 1) && (grid.at(futureX).at(futureY)[2] != '0'))
		for (const auto& position : piece.attakMoves)
			if (move.x == position.x && move.y == position.y)
				return true;
	if (grid.at(futureX).at(futureY)[2] != '0')
		return false;
	if (y == 6 || y == 1)
		if (move.x == piece.specialAllowedMoves.at(0).x && move.y == piece.specialAllowedMoves.at(0).y && CheckPath(x,y,futureX,futureY))
			return true;
	return move.x == piece.allowedMoves.at(0).x && move.y == piece.allowedMoves.at(0).y;
	return false;
}

bool Grid::IsCheck() {
	bool isCheck{ false };
	checkedColor = { 0,0 };
	for (int i{ 1 }; i < 3; ++i) {
		Vector2 kingPosition = kingsPosition.at(i - 1);
		const auto king = pieces->at(5).at(i - 1);
		for (const auto& attacker : king.checkPositions) {
			if (kingPosition.x + attacker.x >= 0 && kingPosition.x + attacker.x < 8 &&
				kingPosition.y + attacker.y >= 0 && kingPosition.y + attacker.y < 8) {
				const auto* piece = GetPiece(grid.at(kingPosition.x + attacker.x).at(kingPosition.y + attacker.y));
				if (piece != NULL) {
					if (piece->color != (&king)->color)
						if (IsMoveAllowed(kingPosition.x + attacker.x, kingPosition.y + attacker.y, kingPosition.x, kingPosition.y)) {
							checkedColor.at(i - 1) = 1;
							isCheck = true;
						}
				}
			}
		}
	}
	return isCheck;
}

bool Grid::IsCheckMate() {
	for (int i{ 1 }; i < 3; ++i) {
		IsCheck();
		if (checkedColor.at(i - 1) == 0)
			continue;
		else {
			for (int j{}; j < size; ++j) {
				for (int k{}; k < size; ++k) {
					if (grid.at(j).at(k)[2] - 48 != i)
						continue;
					else {
						isThereAnyMoves = false;
					}
				}
			}
		}
	}
	return false;
}

void Grid::ChangePiecePosition(int x, int y, int futureX, int futureY, std::string idX, std::string idFutureX) {
	if (idX[2] == '0' && idFutureX[2] == '0') {
		grid.at(futureX).at(futureY)[1] = grid.at(x).at(y)[1];
		grid.at(futureX).at(futureY)[2] = grid.at(x).at(y)[2];
		grid.at(x).at(y)[1] = '0';
		grid.at(x).at(y)[2] = '0';
	}
	else {
		grid.at(x).at(y)[1] = idFutureX[1];
		grid.at(x).at(y)[2] = idFutureX[2];
		grid.at(futureX).at(futureY)[1] = idX[1];
		grid.at(futureX).at(futureY)[2] = idX[2];
	}
	
}

void Grid::Update() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !down) {
		down = true;
		if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != '0' && grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48 != lastColorToMove) {
			position.x = (GetMouseX() - GetMouseX() % 100) / 100;
			position.y = (GetMouseY() - GetMouseY() % 100) / 100;
		}
		else
			position = { -1, -1 };
	}
	else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		if (down && position.x != -1 && position.y != -1 && 
			(GetMouseX() - GetMouseX() % 100) / 100 >= 0 && (GetMouseX() - GetMouseX() % 100) / 100 < size &&
			(GetMouseY() - GetMouseY() % 100) / 100 >= 0 && (GetMouseY() - GetMouseY() % 100) / 100 < size) {
			if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != grid.at(position.x).at(position.y)[2] &&
				IsMoveAllowed(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100) &&
				grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[1] != '6')
			{
				std::string helperIdX{ grid.at(position.x).at(position.y) };
				std::string helperIdFutureX{ grid.at((GetMouseY() - GetMouseY() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100) };
				if (grid.at(position.x).at(position.y)[1] == '6')
					kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)(GetMouseX() - GetMouseX() % 100) / 100,(float)(GetMouseY() - GetMouseY() % 100) / 100 };

				ChangePiecePosition(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100);

				lastColorToMove = grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48;
				
				IsCheck();
				if (checkedColor.at(lastColorToMove - 1) == 1) {
					ChangePiecePosition((GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100, position.x, position.y, helperIdX, "000");
					if (grid.at(position.x).at(position.y)[1] == '6')
						kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)position.x,(float)position.y };
					lastColorToMove = (int)(lastColorToMove == 1) + 1;
				}
			}

		}
		position = { -1, -1 };
		down = false;
	}
}