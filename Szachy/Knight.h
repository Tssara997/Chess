#pragma once

#include "Piece.h"

class Knight :
    public Piece
{
private:
    static constexpr int knightId = 2;
public:
    Knight(int color);
    virtual bool Move(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool Attack(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool SpecialMove(int pieceX, int pieceY, int endX, int endY) const override;
    virtual void Draw(int x, int y) const override;
    ~Knight();
};

