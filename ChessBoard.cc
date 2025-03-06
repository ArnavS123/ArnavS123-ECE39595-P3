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

void ChessBoard::createChessPiece(Color col, Type piece, int startRow, int startCol)
{
    // We are initializing the board here, so we need to clean it up (delete whatever is on the current "spot" and then clear it)
    if (board.at(startRow).at(startCol) != nullptr)
    {
        delete board.at(startRow).at(startCol);
        board.at(startRow).at(startCol) = nullptr;
    }
    
    // Now we put the piece at that spot
    if(piece == Pawn)
    {
        board.at(startRow).at(startCol) = new PawnPiece(board, col, startRow, startCol);
    }
    if(piece == Rook)
    {
        //board.at(startRow).at(startCol) = new RookPiece();
    }
    if(piece == Bishop)
    {
        //board.at(startRow).at(startCol) = new BishopPiece();
    }
    if(piece == King)
    {
        //board.at(startRow).at(startCol) = new KingPiece();
    }
}

bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    // = because numRows and numCols tell us how many and we start from 0
    if (toRow < 0 && toRow >= numRows && toCol < 0 && toCol >= numCols) // boundary condition
    {
        ChessPiece* piece = board.at(fromRow).at(fromCol);
        ChessPiece* capturePiece = board.at(toRow).at(toCol);

        // if there does exist a piece to where we wanna move, make sure its not the same color
        if (capturePiece == nullptr || capturePiece->getColor() != piece->getColor()) // capture condition
        {
            return piece->canMoveToLocation(toRow, toCol);
        }
    }
    return(false); // if we fail boundary condition AND fail capture condition
}

//bool ChessBaord::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {}

//bool ChessBoard::isPieceUnderThreat(int row, int column) {}

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