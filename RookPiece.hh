#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece
    {
        private:
            bool moved = false;
        public:
            RookPiece(ChessBoard &board, Color color, int row, int column);
            virtual ChessPiece* copy(ChessBoard &newBoard) const override;
            virtual Type getType() override {return Rook;}
            virtual bool canMoveToLocation(int toRow, int toCol) override;
            virtual const char *toString() override;
    };
}

#endif