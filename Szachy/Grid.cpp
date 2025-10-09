#include "Grid.h"

Grid::Grid() : size{ defSize }, cellSize{ defCellSize }, grid{}, activePiecePos{ new Position{} }, circleColor{ defCircleColor }, rectangleColor{ defRectangleColor },
			   circleRadius{defCircleRadius}, checkMate{ defCheckmate }, colorToMove{ defColorToMove },
	position{ -1, -1 }, checkedColor{ 0,0 },  avaibleMoves{ {}, {}, {}, {}, {}, {}, {} }
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

			if (id[1] - 48 && (!IsPieceActive() || (activePiecePos->x != i || activePiecePos->y != j)))
				pieces.at(id[1] - 48).at(id[2] - 48)->Draw(i * cellSize, j * cellSize);		
		}
	if (IsPieceActive())
		DrawActivePiece();
	DrawPieceAvaibleMoves();
}

void Grid::DrawActivePiece() const
{
	pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48)->Draw(GetMouseX() - cellSize / 2, GetMouseY() - cellSize / 2);
}

void Grid::DrawPieceAvaibleMoves() const
{
	if (!IsPieceActive())
		return;
	for (int i{}; i < size; ++i) {
		for (int j{}; j < size; ++j) {
			Position pos = CreatePositionFromGrid(i, j);
			bool* check;
			if (IsMoveAllowed(pos)) {
				check = CheckIfCheck(pos);
				std::cout << pos.x << ' ' << pos.y << std::endl;
				std::cout << check[0] << check[1] << check[2] << std::endl;
				if ((check[0] && !check[activePiecePos->id[2] - 48 + 1]) || !check[0])
					DrawCircle(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2, circleRadius, circleColor);
			}
				
			if (IsAttackAllowed(pos)) {
				check = CheckIfCheck(pos);
				if ((check[0] && !check[activePiecePos->id[2] - 48 + 1]) || !check[0])
					DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, rectangleColor);
			}
				
		}
	}
}

bool Grid::OutOfBanceCheck(int x, int y) const
{
	return(0 <= x && x <= cellSize * size && 0 <= y && y <= cellSize * size);
}

bool Grid::IsPieceActive() const
{
	return activePiecePos->x >= 0;
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
	if (x < 0) {
		delete activePiecePos;
		activePiecePos = new Position{};
		return ;
	}
	*activePiecePos = CreatePositionFromScreen(x, y);
}

bool Grid::CheckIfCanBeActive(int x, int y)
{
	Position activePos = CreatePositionFromScreen(x, y);
	return activePos.id[1] != '0';

}

Position Grid::CreatePositionFromGrid(int x, int y) const
{
	if (x < 0)
		return Position{};
	return Position{ grid.at(x).at(y), x ,y };
}

Position Grid::CreatePositionFromScreen(int x, int y) const {
	if (x < 0)
		return Position{};
	Position pos = CreatePositionFromGrid(x / cellSize, y / cellSize);
	return pos;
}

bool Grid::IsMoveAllowed(const Position &pos) const
{
	if (!IsSquareAvaible(pos))
		return false;
	Piece *pieceTemp = pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48);
	if (pieceTemp->SpecialMove(activePiecePos->x, activePiecePos->y, pos.x, pos.y) || pieceTemp->Move(activePiecePos->x, activePiecePos->y, pos.x, pos.y)) {
		return IsPieceJumping(pos);
	}
	return false;
}

bool Grid::IsAttackAllowed(const Position &pos, const Position *activePiecePos, const Position& changedPos) const
{
	if (activePiecePos->x < 0) {
		activePiecePos = this->activePiecePos;
	}
	if (activePiecePos->id[1] == '0' || grid.at(pos.x).at(pos.y)[2] == activePiecePos->id[2] || IsSquareAvaible(pos)) {
		return false;
	}
	if (pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48)->Attack(activePiecePos->x, activePiecePos->y, pos.x, pos.y)) {
		return IsPieceJumping(pos, activePiecePos, changedPos);
	}
	return false;
}

bool Grid::IsPieceJumping(const Position& pos, const Position* activePiecePos, const Position& changedPos) const
{
	if (activePiecePos->x < 0)
		activePiecePos = this->activePiecePos;
	if (activePiecePos->id[1] == '2')
		return true;
	int changeX = (pos.x - activePiecePos->x == 0) ? changeX = 0 : (pos.x - activePiecePos->x) / abs(pos.x - activePiecePos->x);
	int changeY = (pos.y - activePiecePos->y == 0) ? changeY = 0 : (pos.y - activePiecePos->y) / abs(pos.y - activePiecePos->y);
	int i{ 1 };
	Position changePos = CreatePositionFromGrid(activePiecePos->x, activePiecePos->y);
	while ((activePiecePos->x + i * changeX != pos.x) || (activePiecePos->y + i * changeY != pos.y) || !OutOfBanceCheck(activePiecePos->x + i*changeX, activePiecePos->y + i*changeY)) {
		if (activePiecePos->x + i * changeX == changedPos.x && activePiecePos->y + i * changeY == changedPos.y) {
			if (this->activePiecePos->id[1] != '0')
				return false;
		}
		else {
			changePos = CreatePositionFromGrid(activePiecePos->x + i * changeX, activePiecePos->y + i * changeY);
			if (changePos.id[1] != '0')
				return false;
		}
		++i;
	}
	return true;
}

void Grid::Move(int x, int y)
{
	if (!IsPieceActive() || !OutOfBanceCheck(x, y))
		return;
	Position pos = CreatePositionFromScreen(x, y);
	if (IsMoveAllowed(pos) || IsAttackAllowed(pos)) {
		grid.at(pos.x).at(pos.y)[1] = activePiecePos->id[1];
		grid.at(pos.x).at(pos.y)[2] = activePiecePos->id[2];
		grid.at(activePiecePos->x).at(activePiecePos->y)[1] = '0';
		grid.at(activePiecePos->x).at(activePiecePos->y)[2] = '0';
	}
}

bool* Grid::CheckIfCheck(const Position& pos) const
{
	bool* checks{ nullptr };
	if (activePiecePos->id[1] == '6') {
		checks = new bool[1] {false};
		return checks;
	}
	Position kingPos0 = CreatePositionFromGrid(kingsPosition.at(0).x, kingsPosition.at(0).y);
	Position kingPos1 = CreatePositionFromGrid(kingsPosition.at(1).x, kingsPosition.at(1).y);
	Position* tempPos = new Position{};
	for (int i{}; i < size; ++i) {
		for (int j{}; j < size; ++j) {

			if (pos.x == i && pos.y == j) {
				tempPos = new Position{activePiecePos->id, i, j};
			} else 
				*tempPos = CreatePositionFromGrid(i, j);

			if (activePiecePos->x == i && activePiecePos->y == j)
				tempPos = new Position{ pos.id, i, j };

			if (kingPos0.x != i || kingPos0.y != j)
				if (IsAttackAllowed(kingPos0, tempPos, pos)) {
					delete tempPos;
					checks = new bool[3] {true, true, false};
					return checks;
				}
				
			if (kingPos1.x != i || kingPos1.y != j) 
				if (IsAttackAllowed(kingPos1, tempPos, pos)) {
					delete tempPos;
					checks = new bool[3]{ true, false, true };
					return checks;
				}
		}
	}
	delete tempPos;
	checks = new bool[1]{ false };
	return checks;
}