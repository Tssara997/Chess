#pragma once

#include "Piece.h"

class Rook :
    public Piece
{
private:
    static constexpr int rookId = 4;
public:
    Rook(int color);
    virtual bool Move(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool Attack(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool SpecialMove(int pieceX, int pieceY, int endX, int endY) const override;
    virtual void Draw(int x, int y) const override;
    ~Rook();
};