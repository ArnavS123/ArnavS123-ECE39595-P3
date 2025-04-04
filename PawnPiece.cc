#include "PawnPiece.hh"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

using Student::PawnPiece;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column), first_move(true)
{
}

Student::ChessPiece* PawnPiece::copy(ChessBoard &newBoard) const
{
    return new PawnPiece(newBoard, this->getColor(), this->getRow(), this->getColumn());
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
        dir = -1; //up 
    }
    else
    {
        dir = 1; //down
    }

    //note: only have to worry about row currently
    // Just moving forward
    if(toCol == currCol)
    {
        int rowSpace = toRow - currRow;
        if(rowSpace == dir) //one step
        {
            if (board.getPiece(toRow, toCol) == nullptr)
            {
                return(true);
            }
        }

	if(rowSpace == 2*dir) 
	{
	   if(board.getPiece(toRow, toCol) == nullptr && board.getPiece(toRow - dir,toCol) == nullptr)
	   {		   
	      if(color == Black && currRow == 1) 
	      {
	        return true;
	      }
	      else if(color == White && currRow == (board.getNumRows() - 2))
	      {
		    return true;
	      }
	   } 
	}	

        /*if(rowSpace == 2*dir && first_move == true) //two steps (ensure that this is the first move)
        {
            // 2nd condition is VERY IMP to implement going forward
            // we cannot move to a space if another piece is in the way
            // bishop and rook will need this logic too
            if (board.getPiece(toRow, toCol) == nullptr && board.getPiece(currRow + dir, currCol) == nullptr)
            {
                first_move = false; // Unsure if this goes here, but this seems like the best spot
                return(true);
            }
        }*/
    }
    // Capture piece
    if ((abs(toCol - currCol) == 1) && (toRow - currRow == dir)) // diagonal
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