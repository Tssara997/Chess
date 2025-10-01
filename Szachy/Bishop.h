#pragma once

#include "Piece.h"

class Bishop :
    public Piece
{
private:
    static constexpr int bishopId = 3;

public:
    Bishop(int color);
    virtual bool Move(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool Attack(int pieceX, int pieceY, int endX, int endY) const override;
    virtual bool SpecialMove(int pieceX, int pieceY, int endX, int endY) const override;
    virtual void Draw(int x, int y) const override;
    ~Bishop();
};

