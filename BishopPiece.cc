#include "BishopPiece.hh"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

using Student::BishopPiece;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
}

Student::ChessPiece* BishopPiece::copy(ChessBoard &newBoard) const
{
    return new BishopPiece(newBoard, this->getColor(), this->getRow(), this->getColumn());
}

bool BishopPiece::canMoveToLocation(int toRow, int toCol)
{
    int currRow = getRow();
    int currCol = getColumn();

    //can't move to same pos
    if(toRow == currRow && toCol == currCol)
    {
        return false;
    }

    int row_diff = abs(toRow - currRow);
    int col_diff = abs(toCol - currCol);

    if(row_diff != col_diff) //diagonal means row and col difference should be same
    {
        return false;
    }

    int tempRow = currRow;
    int tempCol = currCol;
    for(int i = 0; i < row_diff; i++)
    {
        if (toRow > currRow) // up or down
        {
            tempRow++;
        }
        else
        {
            tempRow--;
        }

        if (toCol > currCol) // right or left
        {
            tempCol++;
        }
        else
        {
            tempCol--;
        }

        if(board.getPiece(tempRow, tempCol) != nullptr)
        {
            if (tempRow == toRow) // This is the end of our loop, if there is an enemy there, we can move and kill it
            {
                return(true);
            }
            return false;
        }
    }
    
    return(true);
}

const char* BishopPiece::toString()
{
    Color col = getColor();

    if (col == White)
    {
        return("♗"); // this is white bishop
    }
    else
    {
        return("♝"); // this is black bishop
    }
}