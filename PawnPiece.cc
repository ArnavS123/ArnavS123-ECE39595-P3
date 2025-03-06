#include "PawnPiece.hh"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

using Student::PawnPiece;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column), first_move(true)
{
}

//pawn can move up and down depending on color by one square (remember: pawn can move two spaces from starting pos)
bool PawnPiece::canMoveToLocation(int toRow, int toCol)
{
    int currRow = getRow();
    int currCol = getColumn();

    //can't move to same pos
    if(toRow == currRow && toCol == currCol)
    {
        return false;
    }

    //white is going up, black is going down
    int dir; //direction that the pawn is moving
    if(getColor() == White)
    {
        dir = 1; // up
    }
    else
    {
        dir = -1; // down
    }

    //note: only have to worry about row currently
    if(toCol = currCol)
    {
        int rowSpace = toRow - currRow;
        if(rowSpace == dir) //one step
        {

        }
        if(rowSpace == 2*dir) //two steps
        {
            
        }
    }
}

const char* PawnPiece::toString()
{
    Color col = getColor();

    if (col == White)
    {
        return("♙");
    }
    else
    {
        return("♟");
    }
}