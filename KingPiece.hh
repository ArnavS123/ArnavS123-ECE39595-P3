#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KingPiece : public ChessPiece
    {
        public:
            KingPiece(ChessBoard &board, Color color, int row, int column);
            virtual ChessPiece* copy(ChessBoard &newBoard) const override;
            virtual Type getType() override {return King;}
            virtual bool canMoveToLocation(int toRow, int toCol) override;
            virtual const char *toString() override;
    };
}

#endif