#pragma once

#include "Piece.h"

class Pawn :
    public Piece
{
private:
    static constexpr int pawnId = 1;
public:
    Pawn(int color);
    virtual bool Move(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool Attack(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool SpecialMove(int pieceX, int pieceY, int endX, int endY) const override;
    virtual void Draw(int x, int y) const override;
    ~Pawn();
};

