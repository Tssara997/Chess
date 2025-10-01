#include "Grid.h"

Grid::Grid() : size{ defSize }, cellSize{ defCellSize }, grid{}, activePiecePos{},
	down{ false }, position{ -1, -1 }, lastColorToMove{ 2 }, checkedColor{ 0,0 }, checkMate{ false }, avaibleMoves{ {}, {}, {}, {}, {}, {}, {} }
{
	kingsPosition = { {4,7},{4,0} };
	CreatePieces();
	CreateGrid();
}

void Grid::CreatePieces() {
	pieces.push_back({ });
	pieces.push_back({ new Pawn{0}, new Pawn{1} });
	pieces.push_back({ new Knight{0}, new Knight{1} });
	pieces.push_back({ new Bishop{0}, new Bishop{1} });
	pieces.push_back({ new Rook{0}, new Rook{1} });
	pieces.push_back({ new Queen{0}, new Queen{1} });
	pieces.push_back({ new King{0}, new King{1} });
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

void Grid::Draw() const {
	std::string id;
	for (int i{}; i < size; ++i)
		for (int j{}; j < size; ++j) {
			id = grid.at(i).at(j);
			if (id[0] - 48)
				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, LIGHTGRAY);
			else
				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, DARKGREEN);

			if (id[1] - 48 && (activePiecePos.x != i || activePiecePos.y != j))
				pieces.at(id[1] - 48).at(id[2] - 48)->Draw(i * cellSize, j * cellSize);		
		}
	if (IsPieceActive())
		DrawActivePiece();
}

void Grid::DrawActivePiece() const
{
	pieces.at(activePiecePos.id[1] - 48).at(activePiecePos.id[2] - 48)->Draw(GetMouseX() - cellSize / 2, GetMouseY() - cellSize / 2);
}

bool Grid::OutOfBanceCheck(int x, int y) const
{
	return(0 <= x && x <= cellSize * size && 0 <= y && y <= cellSize * size);
}

bool Grid::IsPieceActive() const
{
	return activePiecePos.x >= 0;
}

bool Grid::IsSquareAvaible(const Position& pos) const
{
	return grid.at(pos.x).at(pos.y)[1] == '0';
}

bool Grid::CanAttack(const Position& pos) const
{
	return !IsSquareAvaible(pos) && grid.at(pos.x).at(pos.y)[2] != pos.id[2];
}

void Grid::SetActivePiece(int x, int y)
{
	activePiecePos = CreatePosition(x, y);
}

bool Grid::CheckIfCanBeActive(int x, int y)
{
	Position activePos = CreatePosition(x, y);
	return activePos.id[1] != '0';

}

Position Grid::CreatePosition(int x, int y) {
	if (x < 0)
		return Position{};
	Position pos{};
	pos.x = x / cellSize;
	pos.y = y / cellSize;
	pos.id = grid.at(pos.x).at(pos.y);
	return pos;
}

bool Grid::IsMoveAllowed(const Position &pos) const
{
	if (!IsSquareAvaible(pos))
		return false;
	Piece *pieceTemp = pieces.at(activePiecePos.id[1] - 48).at(activePiecePos.id[2] - 48);
	return pieceTemp->SpecialMove(activePiecePos.x, activePiecePos.y, pos.x, pos.y) || pieceTemp->Move(activePiecePos.x, activePiecePos.y, pos.x, pos.y);
}

bool Grid::IsAttackAllowed(const Position &pos) const
{
	if (grid.at(pos.x).at(pos.y)[2] == activePiecePos.id[2] || IsSquareAvaible(pos)) {
		return false;
	}
	std::cout << (pieces.at(activePiecePos.id[1] - 48).at(activePiecePos.id[2] - 48)->Attack(activePiecePos.x, activePiecePos.y, pos.x, pos.y)) << std::endl;
	return pieces.at(activePiecePos.id[1] - 48).at(activePiecePos.id[2] - 48)->Attack(activePiecePos.x, activePiecePos.y, pos.x, pos.y);
}

void Grid::Move(int x, int y)
{
	if (!IsPieceActive() || !OutOfBanceCheck(x, y))
		return;
	Position pos = CreatePosition(x, y);
	if (IsMoveAllowed(pos) || IsAttackAllowed(pos)) {
		grid.at(pos.x).at(pos.y)[1] = activePiecePos.id[1];
		grid.at(pos.x).at(pos.y)[2] = activePiecePos.id[2];
		grid.at(activePiecePos.x).at(activePiecePos.y)[1] = '0';
		grid.at(activePiecePos.x).at(activePiecePos.y)[2] = '0';
	}
}

//Piece* Grid::GetPiece(std::string id) const {
//	int pieceId = id[1] - 49;
//	int colorId = id[2] - 49;
//	if (pieceId >= 0 && pieceId <= 5)
//		return &pieces->at(pieceId).at(colorId);
//	return NULL;
//}
//
//void Grid::GetTexture(std::string id, int x, int y) const {
//	auto piece = GetPiece(id);
//	if (piece != NULL)
//		DrawTexture(piece->texture, x, y, WHITE);
//}
//
//void Grid::Draw() const {
//	Texture2D ct{};
//	for (int i{}; i < size; ++i)
//		for (int j{}; j < size; ++j) {
//			if (grid.at(i).at(j)[0] == '1')
//				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, LIGHTGRAY);
//			else
//				DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, DARKGREEN);
//
//			if ((position.x != i || position.y != j) && grid.at(i).at(j)[1] != '0') {
//				GetTexture(grid.at(i).at(j), i * cellSize, j * cellSize);
//			}
//		}
//
//	if (position.x != -1 && position.y != -1) {
//		if (!checkMate)
//			//DrawPath(position.x, position.y); 
//			GetTexture(grid.at(position.x).at(position.y), GetMouseX() - cellSize / 2, GetMouseY() - cellSize / 2);
//	}
//}
//
//void Grid::DrawPath(int x, int y){
//	AvaibleMoves((lastColorToMove == 1)  +  1);
//	double radius{ 20 };
//	auto piece = GetPiece(grid.at(x).at(y));
//	for (const auto move : avaibleMoves.at(piece->id)) {
//		if (piece->id == 1) {
//			if (((move.x == x + piece->allowedMoves.at(0).x && move.y == y + piece->allowedMoves.at(0).y) ||
//				((y == 1 || y == 6) && move.x == x + piece->specialAllowedMoves.at(0).x && move.y == y + piece->specialAllowedMoves.at(0).y)) &&
//				grid.at(move.x).at(move.y)[2] == '0')
//				DrawCircle(((move.x) * cellSize + cellSize / 2), ((move.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
//			for (const auto attack: piece->attakMoves)
//				if(move.x == x + attack.x && move.y == y + attack.y && grid.at(move.x).at(move.y)[2] - 48 != 0 && grid.at(move.x).at(move.y)[2] - 48 != piece->color)
//					DrawRectangle((move.x) * cellSize, (move.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
//		}
//		else if (piece->id != 5 && piece->id != 6) {
//			for (const auto checkMove : piece->allowedMoves) {
//				if (move.x == x + checkMove.x && move.y == y + checkMove.y) {
//					if (grid.at(move.x).at(move.y)[2] == '0')
//						DrawCircle(((move.x) * cellSize + cellSize / 2), ((move.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
//					else if (grid.at(move.x).at(move.y)[2] - 48 != piece->color)
//						DrawRectangle((move.x) * cellSize, (move.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
//				}
//			}
//		}
//		else if(grid.at(move.x).at(move.y)[2] == '0')
//			DrawCircle(((move.x) * cellSize + cellSize / 2), ((move.y) * cellSize + cellSize / 2), radius, { 133,133,133,200 });
//		else if (grid.at(move.x).at(move.y)[2] - 48  != piece->color)
//			DrawRectangle((move.x) * cellSize, (move.y) * cellSize, cellSize, cellSize, { 220,20,60, 100 });
//	}
//}
//
//void Grid::AvaibleMoves(int color) {
//	avaibleMoves.clear();
//	avaibleMoves = { {}, {}, {}, {}, {}, {}, {} };
//	for (int x{}; x < size; ++x) {
//		for (int y{}; y < size; y++) {
//			std::string helperIdX{}, helperIdFutureX;
//			bool check{ false };
//			const auto piece = GetPiece(grid.at(x).at(y));
//			if (piece == NULL || piece->color != color)
//				continue;
//			else {
//				for (const auto& position : piece->allowedMoves) {
//					if (position.x + x < size && position.x + x >= 0 && position.y + y < size && position.y + y >= 0 && grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color) {
//						helperIdX = grid.at(x).at(y);
//						helperIdFutureX = grid.at(x + position.x).at(y + position.y);
//						ChangePiecePosition(x, y, x + position.x, y + position.y);
//						IsCheck();
//						check = checkedColor.at(piece->color - 1) == 1;
//						ChangePiecePosition(x + position.x, y + position.y, x, y, helperIdX, helperIdFutureX);
//						if (piece->id == 2) {
//							if (!check) {
//								if (grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color) {
//									avaibleMoves.at(piece->id).push_back({ x + position.x, y + position.y });
//								}
//							}
//
//						}
//
//						if (piece->id == 1) {
//							if (grid.at(x + position.x).at(y + position.y)[2] == '0' && !check)
//								avaibleMoves.at(piece->id).push_back({ x + position.x, y + position.y });
//							for (const auto& attackMove : piece->attakMoves)
//								if (x + attackMove.x >= 0 && x + attackMove.x < 8 && y + attackMove.y + y >= 0 && y + attackMove.y < 8) {
//									helperIdX = grid.at(x).at(y);
//									helperIdFutureX = grid.at(x + attackMove.x).at(y + attackMove.y);
//									ChangePiecePosition(x, y, x + attackMove.x, y + attackMove.y);
//									IsCheck();
//									check = checkedColor.at(piece->color - 1) == 1;
//									ChangePiecePosition(x + attackMove.x, y + attackMove.y, x, y, helperIdX, helperIdFutureX);
//									if (grid.at(x + attackMove.x).at(y + attackMove.y)[2] - 48 != piece->color && grid.at(x + attackMove.x).at(y + attackMove.y)[2] != '0' && !check) {
//										avaibleMoves.at(piece->id).push_back({ x + attackMove.x, y + attackMove.y });
//									}
//								}
//							if ((y == 1 || y == 6)) {
//								if (grid.at(x + piece->specialAllowedMoves.at(0).x).at(y + piece->specialAllowedMoves.at(0).y)[2] == '0' && CheckPath(x, y, x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y)) {
//									helperIdX = grid.at(x).at(y);
//									helperIdFutureX = grid.at(x + piece->specialAllowedMoves.at(0).x).at(y + piece->specialAllowedMoves.at(0).y);
//									ChangePiecePosition(x, y, x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y);
//									IsCheck();
//									check = checkedColor.at(piece->color - 1) == 1;
//									ChangePiecePosition(x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y, x, y, helperIdX, helperIdFutureX);
//									if (!check) {
//										avaibleMoves.at(piece->id).push_back({ x + piece->specialAllowedMoves.at(0).x, y + piece->specialAllowedMoves.at(0).y });
//									}
//								}
//							}
//						}
//
//						else if (piece->id == 6) {
//							if (grid.at(x + position.x).at(y + position.y)[2] - 48 == piece->color)
//								continue;
//							else {
//								Vector2 helperPosition = kingsPosition.at(piece->color - 1);
//								kingsPosition.at(piece->color - 1) = { x + position.x, y + position.y };
//								helperIdX = grid.at(x).at(y);
//								helperIdFutureX = grid.at(x + position.x).at(y + position.y);
//								ChangePiecePosition(x, y, x + position.x, y + position.y);
//								IsCheck();
//								ChangePiecePosition(x + position.x, y + position.y, x, y, helperIdX, helperIdFutureX);
//								kingsPosition.at(piece->color - 1) = helperPosition;
//								check = checkedColor.at(piece->color - 1) == 1;
//								if (grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color && !check) {
//									avaibleMoves.at(piece->id).push_back({ x + position.x, y + position.y });
//								}
//							}
//						}
//
//						else if (CheckPath(x, y, position.x + x, position.y + y)) {
//							if (!check && grid.at(x + position.x).at(y + position.y)[2] - 48 != piece->color) {
//								avaibleMoves.at(piece->id).push_back({ x + position.x, y + position.y });
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//bool Grid::CheckPath(int x, int y, int futureX, int futureY) const {
//	if (grid.at(x).at(y)[1] == '2')
//		return grid.at(futureX).at(futureY)[2] != grid.at(x).at(y)[2];
//	int moveX{ x != futureX };
//	int moveY{ y != futureY };
//	int i{ 1 };
//	if (x > futureX)
//		moveX = -1;
//	else if (x < futureX)
//		moveX = 1;
//	if (y > futureY)
//		moveY = -1;
//	else if (y < futureY)
//		moveY = 1;
//
//	while (x + i * moveX != futureX || y + i * moveY != futureY) {
//		if (grid.at(x + i * moveX).at(y + i * moveY)[2] != '0')
//			return false;
//		i++;
//	}
//
//	return true;
//}
//
//bool Grid::IsMoveAllowed(int x, int y, int futureX, int futureY) const {
//	bool allowed = false;
//	const auto piece = GetPiece(grid.at(x).at(y));
//	Vector2 move = { abs(x - futureX), abs(y - futureY) };
//	if (piece != NULL) {
//		if (piece->id == 1)
//			return IsPawnMoveAllowed(x, y, futureX, futureY);
//		else {
//			for (const auto& position : piece->allowedMoves) {
//				if (position.x == move.x && position.y == move.y) {
//					allowed = true;
//					break;
//				}
//
//			}
//			if (allowed && piece->id != 2)
//				return CheckPath(x, y, futureX, futureY);
//		}
//	}
//	return allowed;
//}
//
//bool Grid::IsPawnMoveAllowed(int x, int y, int futureX, int futureY) const
//{
//	std::string id = grid.at(x).at(y);
//	const auto piece = pieces->at(0).at(id[2] - 49);
//	Vector2 move = { futureX - x, futureY - y };
//	if ((grid.at(futureX).at(futureY)[2] - 48 != (&piece)->color == 1) && (grid.at(futureX).at(futureY)[2] != '0'))
//		for (const auto& position : piece.attakMoves)
//			if (move.x == position.x && move.y == position.y)
//				return true;
//	if (grid.at(futureX).at(futureY)[2] != '0')
//		return false;
//	if (y == 6 || y == 1)
//		if (move.x == piece.specialAllowedMoves.at(0).x && move.y == piece.specialAllowedMoves.at(0).y && CheckPath(x,y,futureX,futureY))
//			return true;
//	return move.x == piece.allowedMoves.at(0).x && move.y == piece.allowedMoves.at(0).y;
//	return false;
//}
//
//bool Grid::IsCheck() {
//	bool isCheck{ false };
//	checkedColor = { 0,0 };
//	for (int i{ 1 }; i < 3; ++i) {
//		Vector2 kingPosition = kingsPosition.at(i - 1);
//		const auto king = pieces->at(5).at(i - 1);
//		for (const auto& attacker : king.checkPositions) {
//			if (kingPosition.x + attacker.x >= 0 && kingPosition.x + attacker.x < 8 &&
//				kingPosition.y + attacker.y >= 0 && kingPosition.y + attacker.y < 8) {
//				const auto* piece = GetPiece(grid.at(kingPosition.x + attacker.x).at(kingPosition.y + attacker.y));
//				if (piece != NULL) {
//					if (piece->color != (&king)->color)
//						if (IsMoveAllowed(kingPosition.x + attacker.x, kingPosition.y + attacker.y, kingPosition.x, kingPosition.y)) {
//							checkedColor.at(i - 1) = 1;
//							isCheck = true;
//						}
//				}
//			}
//		}
//	}
//	return isCheck;
//}
//
//bool Grid::IsCheckMate() {
//	AvaibleMoves((lastColorToMove == 1) + 1);
//	for (const auto move : avaibleMoves) {
//		if (move.size() > 0)
//			return false;
//	}
//	checkMate = true;
//	return true;
//}
//
//void Grid::ChangePiecePosition(int x, int y, int futureX, int futureY, std::string idX, std::string idFutureX) {
//	if (idX[2] == '0' && idFutureX[2] == '0') {
//		grid.at(futureX).at(futureY)[1] = grid.at(x).at(y)[1];
//		grid.at(futureX).at(futureY)[2] = grid.at(x).at(y)[2];
//		grid.at(x).at(y)[1] = '0';
//		grid.at(x).at(y)[2] = '0';
//	}
//	else {
//		grid.at(x).at(y)[1] = idFutureX[1];
//		grid.at(x).at(y)[2] = idFutureX[2];
//		grid.at(futureX).at(futureY)[1] = idX[1];
//		grid.at(futureX).at(futureY)[2] = idX[2];
//	}
//	
//}
//
//void Grid::Update() {
//	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !down && !checkMate) {
//		down = true;
//		if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != '0' && grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48 != lastColorToMove) {
//			position.x = (GetMouseX() - GetMouseX() % 100) / 100;
//			position.y = (GetMouseY() - GetMouseY() % 100) / 100;
//		}
//		else
//			position = { -1, -1 };
//	}
//	else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
//		if (down && position.x != -1 && position.y != -1 && 
//			(GetMouseX() - GetMouseX() % 100) / 100 >= 0 && (GetMouseX() - GetMouseX() % 100) / 100 < size &&
//			(GetMouseY() - GetMouseY() % 100) / 100 >= 0 && (GetMouseY() - GetMouseY() % 100) / 100 < size) {
//			if (grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] != grid.at(position.x).at(position.y)[2] &&
//				IsMoveAllowed(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100) &&
//				grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[1] != '6' && 
//				!checkMate)
//			{
//				std::string helperIdX{ grid.at(position.x).at(position.y) };
//				std::string helperIdFutureX{ grid.at((GetMouseY() - GetMouseY() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100) };
//				if (grid.at(position.x).at(position.y)[1] == '6')
//					kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)(GetMouseX() - GetMouseX() % 100) / 100,(float)(GetMouseY() - GetMouseY() % 100) / 100 };
//
//				ChangePiecePosition(position.x, position.y, (GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100);
//
//				lastColorToMove = grid.at((GetMouseX() - GetMouseX() % 100) / 100).at((GetMouseY() - GetMouseY() % 100) / 100)[2] - 48;
//
//				IsCheck();
//				if (IsCheck())
//					IsCheckMate();
//				if (checkedColor.at(lastColorToMove - 1) == 1) {
//					ChangePiecePosition((GetMouseX() - GetMouseX() % 100) / 100, (GetMouseY() - GetMouseY() % 100) / 100, position.x, position.y, helperIdX, "000");
//					if (grid.at(position.x).at(position.y)[1] == '6')
//						kingsPosition.at(grid.at(position.x).at(position.y)[2] - 49) = { (float)position.x,(float)position.y };
//					lastColorToMove = (int)(lastColorToMove == 1) + 1;
//				}
//			}
//
//		}
//		position = { -1, -1 };
//		down = false;
//	}
//}