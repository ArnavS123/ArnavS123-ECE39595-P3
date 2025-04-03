#include "KingPiece.hh"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

using Student::KingPiece;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column), moved_kingW(false), moved_kingB(false), moved_rookLW(false), moved_rookLB(false), moved_rookRW(false), moved_rookRB(false)
{
}

Student::ChessPiece* KingPiece::copy(ChessBoard &newBoard) const
{
    return new KingPiece(newBoard, this->getColor(), this->getRow(), this->getColumn());
}

bool KingPiece::canMoveToLocation(int toRow, int toCol)
{
    int currRow = getRow();
    int currCol = getColumn();
    Color color = getColor();
    bool emptyWR = false;
    bool emptyWL = false;
    bool emptyBR = false;
    bool emptyBL = false;

    if (!(color == Black && currRow == 0 && currCol == 4))
    {
        moved_kingB = true;
    }
    if (!(color == White && currRow == 7 && currCol == 4))
    {
        moved_kingW = true;
    }

    if (board.getPiece(0, 0) == nullptr)
    {
        moved_rookLB = true;
    }
    if (board.getPiece(0, 7) == nullptr)
    {
        moved_rookRB = true;
    }
    if (board.getPiece(7, 0) == nullptr)
    {
        moved_rookLW = true;
    }
    if (board.getPiece(7, 7) == nullptr)
    {
        moved_rookRW = true;
    }

    if (board.getPiece(0, 1) == nullptr && board.getPiece(0, 2) == nullptr && board.getPiece(0, 3) == nullptr)
    {
        emptyBL = true;
    }
    if (board.getPiece(0, 5) == nullptr && board.getPiece(0, 6) == nullptr)
    {
        emptyBR = true;
    }
    if (board.getPiece(7, 1) == nullptr && board.getPiece(7, 2) == nullptr && board.getPiece(7, 3) == nullptr)
    {
        emptyWL = true;
    }
    if (board.getPiece(7, 5) == nullptr && board.getPiece(7, 6) == nullptr)
    {
        emptyWR = true;
    }

    //can't move to same pos
    if(toRow == currRow && toCol == currCol)
    {
        return false;
    }

    // The interesting thing about moving the king is that he can move to any spot adjacent to him
    // we already check boundary condition in isValidMove (so no need to do that here too)
    if (abs(toRow - currRow) <= 1 && abs(toCol - currCol) <= 1)
    {
        // now we gotta implement a feature that prevents the king from moving to a square if it is dangerous BUT
        // we also need to ensure that movePiece doesn't do anything if moving the king is dangerous
        return(true);
    }
    else if (abs(toCol - currCol) == 2 && abs(toRow - currRow) == 0) // CASTLING
    {
        if (color == White)
        {
            if (moved_kingW == true) {return(false);}
            if (toCol > currCol && emptyWR == true && moved_rookRW == false)
            {
                return(true);
            }
            if (toCol < currCol && emptyWL == true && moved_rookLW == false)
            {
                return(true);
            }
        }
        else // color == Black
        {
            if (moved_kingB == true) {return(false);}
            if (toCol > currCol && emptyBR == true && moved_rookRB == false)
            {
                return(true);
            }
            if (toCol < currCol && emptyBL == true && moved_rookLB == false)
            {
                return(true);
            }
        }
    }
    
    return(false);
}

const char* KingPiece::toString()
{
    Color col = getColor();

    if (col == White)
    {
        return("♔"); // this is white king
    }
    else
    {
        return("♚"); // this is black king
    }
}