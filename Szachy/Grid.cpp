#include "Grid.h"

Grid::Grid() : size{ defSize }, cellSize{ defCellSize }, grid{}, activePiecePos{ new Position{} }, circleColor{ defCircleColor }, rectangleColor{ defRectangleColor },
circleRadius{ defCircleRadius }, checkMate{ defCheckmate }, lastMovedColor{ defLastMovedColor }, avaibleMoves{ {} }
{
	CreatePieces();
	CreateGrid();
	kingsPosition.push_back(CreatePositionFromGrid(4,7));
	kingsPosition.push_back(CreatePositionFromGrid(4, 0));
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
	if (IsPieceActive()) {
		DrawPieceAvaibleMoves();
		DrawActivePiece();
	}
}

void Grid::DrawActivePiece() const
{
	pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48)->Draw(GetMouseX() - cellSize / 2, GetMouseY() - cellSize / 2);
}

void Grid::PieceAvaibleMoves(const Position* pos)
{
	avaibleMoves.clear();

	if (pos->x < 0)
		pos = this->activePiecePos;

	for (int i{}; i < size; ++i) {
		for (int j{}; j < size; ++j) {
			Position tempPos = CreatePositionFromGrid(i, j);
			bool* check;
			if (IsMoveAllowed(tempPos, pos) || IsAttackAllowed(tempPos, pos)) {
				check = CheckIfCheck(tempPos, pos);
				//if ((check[0] && !check[pos->id[2] - 48 + 1]) || !check[0])
				//	avaibleMoves.push_back({ tempPos });
				if (!check[pos->id[2] - 48 + 1])
					avaibleMoves.push_back({ tempPos });
				delete check;
			}
		}
	}
}

void Grid::DrawPieceAvaibleMoves() const
{
	for (const auto& tempPos : avaibleMoves) {
		if (tempPos.id[1] - 48)
			DrawRectangle(tempPos.x * cellSize, tempPos.y * cellSize, cellSize, cellSize, rectangleColor);
		else 
			DrawCircle(tempPos.x * cellSize + cellSize / 2, tempPos.y * cellSize + cellSize / 2, circleRadius, circleColor);
	}
}

bool Grid::OutOfBanceCheck(int x, int y) const
{
    return (0 <= x && x < static_cast<int>(size) && 0 <= y && y < static_cast<int>(size));
}

bool Grid::IsPieceActive() const
{
	return activePiecePos->x >= 0;
}

bool Grid::CanColorMove(int color) const {
	if (color != -1)
		return color != lastMovedColor;
	return lastMovedColor != activePiecePos->id[2] - 48;
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

bool Grid::IsMoveAllowed(const Position &pos, const Position* activePiecePos, const Position& changedPos) const
{
	if (!IsSquareAvaible(pos))
		return false;
	if (activePiecePos->x < 0)
		activePiecePos = this->activePiecePos;
	Piece *pieceTemp = pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48);
	if (pieceTemp->SpecialMove(activePiecePos->x, activePiecePos->y, pos.x, pos.y) || pieceTemp->Move(activePiecePos->x, activePiecePos->y, pos.x, pos.y)) {
		return IsPieceJumping(pos, activePiecePos, changedPos);
	}
	return false;
}

bool Grid::IsAttackAllowed(const Position &pos, const Position *activePiecePos, const Position& changedPos) const
{
	if (activePiecePos->x < 0) {
		activePiecePos = this->activePiecePos;
	}
	if (activePiecePos->id[1] == '0' || pos.id[2] == activePiecePos->id[2] || pos.id[1] == '0') {
		return false;
	}
	if (pieces.at(activePiecePos->id[1] - 48).at(activePiecePos->id[2] - 48)->Attack(activePiecePos->x, activePiecePos->y, pos.x, pos.y)) {
		return IsPieceJumping(pos, activePiecePos, changedPos);
	}
	return false;
}

bool Grid::IsPieceJumping(const Position& pos, const Position* activePiecePos, const Position& changedPos) const
{
	bool checkForChecking{ true };
	if (activePiecePos->x < 0) {
		checkForChecking = !checkForChecking;
		activePiecePos = this->activePiecePos;
	}
	if (activePiecePos->id[1] == '2')
		return true;
	int changeX = (pos.x - activePiecePos->x == 0) ? changeX = 0 : (pos.x - activePiecePos->x) / abs(pos.x - activePiecePos->x);
	int changeY = (pos.y - activePiecePos->y == 0) ? changeY = 0 : (pos.y - activePiecePos->y) / abs(pos.y - activePiecePos->y);
	int i{ 1 };
	Position jumpingPos = CreatePositionFromGrid(activePiecePos->x, activePiecePos->y);
	while ((activePiecePos->x + i * changeX != pos.x) || (activePiecePos->y + i * changeY != pos.y) || !OutOfBanceCheck(activePiecePos->x + i*changeX, activePiecePos->y + i*changeY)) {
		// checking for jumping when we check where the piece can go (DrawAvaibleMoves) so it checks if the piece should be there
		if (activePiecePos->x + i * changeX == changedPos.x && activePiecePos->y + i * changeY == changedPos.y) {
			return false;
		}

		 //checking for jumping when the piece isnt supposed to be there (DrawAvaibleMoves)
		if (checkForChecking)
			if (activePiecePos->x + i * changeX == this->activePiecePos->x && activePiecePos->y + i * changeY == this->activePiecePos->y) {
				++i;
				continue;
			}

		 //checking for jumping when moving piece
		else {
			jumpingPos = CreatePositionFromGrid(activePiecePos->x + i * changeX, activePiecePos->y + i * changeY);
			if (jumpingPos.id[1] != '0')
				return false;
		}
		++i;
	}
	return true;
}

void Grid::Move(int x, int y)
{
    if (!IsPieceActive())
        return;
    if (x < 0 || y < 0 || x > cellSize * static_cast<int>(size) || y > cellSize * static_cast<int>(size))
        return;
    Position pos = CreatePositionFromScreen(x, y);
	if ((IsMoveAllowed(pos) || IsAttackAllowed(pos)) && !CheckIfCheck(pos)[activePiecePos->id[2] - 48 + 1]) {
		lastMovedColor = activePiecePos->id[2] - 48;
		grid.at(pos.x).at(pos.y)[1] = activePiecePos->id[1];
		grid.at(pos.x).at(pos.y)[2] = activePiecePos->id[2];
		grid.at(activePiecePos->x).at(activePiecePos->y)[1] = '0';
		grid.at(activePiecePos->x).at(activePiecePos->y)[2] = '0';
		if (activePiecePos->id[1] == '6') {
			kingsPosition.at(activePiecePos->id[2] - 48) = CreatePositionFromGrid(pos.x, pos.y);
		}
		SetActivePiece(-1, -1);
		IsCheckMate();
	}

}

bool* Grid::CheckIfCheck(const Position& pos, const Position* activePiecePos) const
{
	bool* checks{ nullptr };
	checks = new bool[3] { false, false, false };
	std::vector<Position> kingsPosition = this->kingsPosition;
	if (activePiecePos->x < 0) {
		activePiecePos = this->activePiecePos;
	}
	if (activePiecePos->id[1] == '6') {
		kingsPosition.at(activePiecePos->id[2] - 48) = Position{ activePiecePos->id, pos.x, pos.y };
	}
	Position tempPos = Position{};
	for (int i{}; i < size; ++i) {
		for (int j{}; j < size; ++j) {

			if (pos.x == i && pos.y == j && activePiecePos->id[1] != '6') {
				tempPos = Position{activePiecePos->id, i, j};
			} else 
				tempPos = CreatePositionFromGrid(i, j);

			if (activePiecePos->x == i && activePiecePos->y == j)
				tempPos = new Position{ pos.id, i, j };

			if (kingsPosition.at(0).x != i || kingsPosition.at(0).y != j)
				if (IsAttackAllowed(kingsPosition.at(0), &tempPos, pos)) {
					checks[0] = true;
					checks[1] = true;
				}
				
			if (kingsPosition.at(1).x != i || kingsPosition.at(1).y != j)
				if (IsAttackAllowed(kingsPosition.at(1), &tempPos, pos)) {
					checks[0] = true;
					checks[2] = true;
				}
		}
	}
	return checks;
}

bool Grid::IsCheckMate()
{
	bool* checks;
	checks = CheckIfCheck();

	if (!CheckIfCheck()[0])
		return false;
	
	Position* tempPos = new Position{};
	for (int i{}; i < size; ++i) {
		for (int j{}; j < size; ++j) {
			*tempPos = CreatePositionFromGrid(i, j);
			if (checks[tempPos->id[2] - 48 + 1] && tempPos->id[1] != '0') {
				PieceAvaibleMoves(tempPos);
				if (avaibleMoves.size() > 0) {
					delete checks;
					delete tempPos;
					return false;
				}
			}
		}
	}
	delete checks;
	delete tempPos;
	checkMate = true;
	return true;
}

bool Grid::IsGameOver() const {
	return checkMate;
}

void Grid::Reset()
{
	SetActivePiece(-1, -1);
	grid.clear();
	CreateGrid();
	avaibleMoves.clear();
	lastMovedColor = defLastMovedColor;
	checkMate = defCheckmate;
}
