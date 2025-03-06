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
    Color color = getColor(); // name this color bec col could be column

    //can't move to same pos
    if(toRow == currRow && toCol == currCol)
    {
        return false;
    }

    //white is going up, black is going down
    int dir; //direction that the pawn is moving
    if(color == White)
    {
        dir = 1; // up
    }
    else
    {
        dir = -1; // down
    }

    //note: only have to worry about row currently
    // Just moving forward
    if(toCol == currCol)
    {
        int rowSpace = abs(toRow - currRow);
        if(rowSpace == dir) //one step
        {
            if (board.getPiece(toRow, toCol) == nullptr)
            {
                return(true);
            }
        }
        if(rowSpace == 2*dir && first_move == true) //two steps (ensure that this is the first move)
        {
            // 2nd condition is VERY IMP to implement going forward
            // we cannot move to a space if another piece is in the way
            // bishop and rook will need this logic too
            if (board.getPiece(toRow, toCol) == nullptr && board.getPiece(currRow + dir, currCol) == nullptr)
            {
                return(true);
            }
        }
    }
    // Capture piece
    else if (abs(toCol - currCol) == 1 && toRow - currRow == dir)
    {
        ChessPiece *deadPiece = board.getPiece(toRow, toCol);
        if (deadPiece != nullptr && color != deadPiece->getColor())
        {
            return(true);
        }
    }
    
    return(false);
}

const char* PawnPiece::toString()
{
    Color col = getColor();

    if (col == White)
    {
        return("♙"); // this is white pawn
    }
    else
    {
        return("♟"); // this is black pawn
    }
}