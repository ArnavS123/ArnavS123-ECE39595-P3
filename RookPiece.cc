#include "RookPiece.hh"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

using Student::RookPiece;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
}

bool RookPiece::canMoveToLocation(int toRow, int toCol)
{
    int currRow = getRow();
    int currCol = getColumn();

    //can't move to same pos
    if(toRow == currRow && toCol == currCol)
    {
        return false;
    }

    // Vertical
    if(toCol == currCol)
    {
        int rowSpace = abs(toRow - currRow);
        int tempRow = currRow;
        for(int i = 0; i < rowSpace; i++)
        {
            if (toRow > currRow)
            {
                tempRow++;
            }
            else
            {
                tempRow--;
            }
    
            if(board.getPiece(tempRow, currCol) != nullptr)
            {
                // if (tempRow == toRow) // This is the end of our loop, if there is an enemy there, we can move and kill it
                // {
                //     return(true);
                // }
                return false;
            }
        }
    }
    // Horizontal
    else if(toRow == currRow)
    {
        int colSpace = abs(toCol - currCol);
        int tempCol = currCol;
        for(int i = 0; i < colSpace; i++)
        {
            if (toCol > currCol)
            {
                tempCol++;
            }
            else
            {
                tempCol--;
            }
    
            if(board.getPiece(currRow, tempCol) != nullptr)
            {
                // if (tempCol == toCol) // This is the end of our loop, if there is an enemy there, we can move and kill it
                // {
                //     return(true);
                // }
                return false;
            }
        }
    }
    
    return(true);
}

const char* RookPiece::toString()
{
    Color col = getColor();

    if (col == White)
    {
        return("♖"); // this is white rook
    }
    else
    {
        return("♜"); // this is black rook
    }
}