#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
        private:
            bool first_move;
        public:
            PawnPiece(ChessBoard &board, Color color, int row, int column);
            virtual ChessPiece* copy(ChessBoard &newBoard) const override;
            virtual Type getType() override {return Pawn;}
            virtual bool canMoveToLocation(int toRow, int toCol) override;
            virtual const char *toString() override;
    };
}

#endif