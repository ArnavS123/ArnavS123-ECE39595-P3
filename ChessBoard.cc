#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int num_row, int num_col) : numRows(num_row), numCols(num_col), turn(White),
board(numRows, std::vector<ChessPiece*>(numCols, nullptr))
{
}

// added implementation
ChessBoard::~ChessBoard()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            if (board.at(row).at(col) != nullptr)
            {
                delete board.at(row).at(col);
                board.at(row).at(col) = nullptr;
            }
        }
    }
}

void ChessBoard::createChessPiece(Color col, Type piece, int startRow, int startCol)
{
    // Ensure it's within boundary
    if (startRow < 0 && startRow >= numRows && startCol < 0 && startCol >= numCols)
    {
        return; // ERROR
    }

    // We are initializing the board here, so we need to clean it up (delete whatever is on the current "spot" and then clear it)
    if (board.at(startRow).at(startCol) != nullptr)
    {
        delete board.at(startRow).at(startCol);
        board.at(startRow).at(startCol) = nullptr;
    }
    
    // Now we put the piece at that spot
    if (piece == Pawn)
    {
        board.at(startRow).at(startCol) = new PawnPiece(*this, col, startRow, startCol);
    }
    if (piece == Rook)
    {
        board.at(startRow).at(startCol) = new RookPiece(*this, col, startRow, startCol);
    }
    if (piece == Bishop)
    {
        board.at(startRow).at(startCol) = new BishopPiece(*this, col, startRow, startCol);
    }
    if (piece == King)
    {
        board.at(startRow).at(startCol) = new KingPiece(*this, col, startRow, startCol);
    }
}

bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    // = because numRows and numCols tell us how many and we start from 0
    if (!(fromRow < 0 || fromRow >= numRows || fromCol < 0 || fromCol >= numCols ||
        toRow < 0 || toRow >= numRows || toCol < 0 || toCol >= numCols)) // boundary condition
    {
        ChessPiece* piece = getPiece(fromRow, fromCol);
        if (piece == nullptr) 
        {
            return false; // No piece at (fromRow, fromCol)
        }

        ChessPiece* capturePiece = getPiece(toRow, toCol);
        // if there does exist a piece to where we wanna move, make sure its not the same color
        if (capturePiece == nullptr || capturePiece->getColor() != piece->getColor()) // capture condition
        {
            return piece->canMoveToLocation(toRow, toCol);
        }
    }
    return(false); // if we fail boundary condition OR fail capture condition
}

bool ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
    if (isValidMove(fromRow, fromCol, toRow, toCol) == false)
    {
        return(false);
    }

    ChessPiece* pieceToMove = getPiece(fromRow, fromCol);
    if (pieceToMove == nullptr) 
    {
        return false; // No piece at (fromRow, fromCol)
    }
    
    if(pieceToMove->getColor() != turn)
    {
        return false;
    }

    // get original position of our piece (we want to revert changes IF king is in danger)
    int origin_row = pieceToMove->getRow();
    int origin_col = pieceToMove->getColumn();

    ChessPiece* pieceToCapture = getPiece(toRow, toCol); // could be nullptr (does not matter)

    // removed delete (we are testing king safety right now)
    board.at(toRow).at(toCol) = pieceToMove;
    board.at(fromRow).at(fromCol) = nullptr;
    pieceToMove->setPosition(toRow, toCol); // temp

    // find king of turn's color
    bool found_king = false;
    int kingrow = 0;
    int kingcol = 0;
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            ChessPiece* maybeking = board.at(row).at(col);
            // this position has the king of the same color as turn (pieceToMove)
            if (maybeking != nullptr && maybeking->getType() == King && maybeking->getColor() == pieceToMove->getColor())
            {
                found_king = true;
                kingrow = row;
                kingcol = col;
            }
        }
    }

    // if there is no king on the board OR if king is there but in danger bec of the move
    if (found_king == false || isPieceUnderThreat(kingrow, kingcol))
    {
        // revert
        board.at(fromRow).at(fromCol) = pieceToMove; // move original moving piece back
        board.at(fromRow).at(fromCol) = pieceToCapture; // move original captured piece back
        pieceToMove->setPosition(origin_row, origin_col); // reset pos of moving piece

        return(false);
    }

    // if king = safe, we delete captured piece
    if (board.at(toRow).at(toCol) != nullptr) // if there is a piece there (isValidMove already checks for color)
    {
        delete board.at(toRow).at(toCol);
    }

    // turn does not change if king in danger
    if (turn == White)
    {
        turn = Black;
    }
    else // turn == Black
    {
        turn = White;
    }

    return(true);
}

bool ChessBoard::isPieceUnderThreat(int row, int col)
{
    // loop through entire board
    // check for all enemy pieces (other color)
    // isValidMove() to where curr piece is for the enemy piece
    // from enemy piece to checking piece
    // if a single "collision" is found, stop the function, return true
    // else false

    ChessPiece* currPiece = getPiece(row, col);
    if (currPiece == nullptr) 
    {
        return false; // No piece at (row, col)
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            ChessPiece* piece = getPiece(i,j);
            if(piece != nullptr && piece->getColor() != currPiece->getColor())
            {
                if(isValidMove(i, j, row, col)) //piece can move to curr pos (under threat)
                {
                    return true;
                }
            }
        }
    }

    return(false); //no piece can attack
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}