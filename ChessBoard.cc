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

ChessBoard::ChessBoard(const ChessBoard &other) : numRows(other.numRows), numCols(other.numCols), turn(other.turn), board(numRows, std::vector<ChessPiece*>(numCols, nullptr))
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (other.board.at(i).at(j) != nullptr)
            {
                // Clone the piece from the original board and associate it with *this.
                board.at(i).at(j) = other.board.at(i).at(j)->copy(*this);
            }
        }
    }
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
    // Ensure it's within boundary (changed && --> ||)
    if (startRow < 0 || startRow >= numRows || startCol < 0 || startCol >= numCols)
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

//////////
// NOTE FOR LATER: THREAT FUNCTION IS CALLING ISVALIDMOVE AND ISVALIDMOVE FUNCTION IS CALLING THREAT FUNCTION
//////////

bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    bool castle = false;
    bool castle_attempt = false;

    if (getPiece(fromRow, fromCol)->getType() == King && getPiece(fromRow, fromCol)->getColor() == White && toRow == 0 && toCol == 2)
    {
        castle_attempt = true;
    }
    if (getPiece(fromRow, fromCol)->getType() == King && getPiece(fromRow, fromCol)->getColor() == White && toRow == 0 && toCol == 6)
    {
        castle_attempt = true;
    }
    if (getPiece(fromRow, fromCol)->getType() == King && getPiece(fromRow, fromCol)->getColor() == Black && toRow == 7 && toCol == 2)
    {
        castle_attempt = true;
    }
    if (getPiece(fromRow, fromCol)->getType() == King && getPiece(fromRow, fromCol)->getColor() == White && toRow == 7 && toCol == 6)
    {
        castle_attempt = true;
    }

    // is castle ok?
    if (getPiece(0, 0)->getColor() == White && getPiece(0, 0)->getType() == Rook && isPieceUnderThreat(fromRow, fromCol) == false)
    {
        castle = true;
    }
    if (getPiece(0, 7)->getColor() == White && getPiece(0, 7)->getType() == Rook && isPieceUnderThreat(fromRow, fromCol) == false)
    {
        castle = true;
    }
    if (getPiece(7, 0)->getColor() == Black && getPiece(7, 0)->getType() == Rook && isPieceUnderThreat(fromRow, fromCol) == false)
    {
        castle = true;
    }
    if (getPiece(7, 7)->getColor() == Black && getPiece(7, 7)->getType() == Rook && isPieceUnderThreat(fromRow, fromCol) == false)
    {
        castle = true;
    }

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
            ChessBoard tempBoard(*this);  //use copy constructor
            ChessPiece* tempPiece = tempBoard.getPiece(fromRow, fromCol);
            
            bool king_safe = false;
            
            if (tempBoard.board.at(toRow).at(toCol) != nullptr) 
            {
                delete tempBoard.board.at(toRow).at(toCol);
            }

            tempBoard.board.at(toRow).at(toCol) = tempPiece;
            tempBoard.board.at(fromRow).at(fromCol) = nullptr;
            tempPiece->setPosition(toRow, toCol); // temp

            // find king of turn's color
            bool found_king = false;
            int kingrow = -1;
            int kingcol = -1;
            for (int row = 0; row < numRows; row++)
            {
                for (int col = 0; col < numCols; col++)
                {
                    ChessPiece* maybeking = tempBoard.getPiece(row,col);
                    // this position has the king of the same color as turn
                    if (maybeking != nullptr && maybeking->getType() == King && maybeking->getColor() == turn)
                    {
                        found_king = true;
                        kingrow = row;
                        kingcol = col;
                        break; // time save (gradescope is slow)
                    }
                }
                if (kingrow != -1 && kingcol != -1)
                {
                    break; // more time save
                }
            }

            // if there is no king on the board OR if king is there but in danger bec of the move
            if (found_king == false || !(tempBoard.isPieceUnderThreat(kingrow, kingcol)))
            {
                if (castle_attempt == true && castle == true)
                {
                    // TODO: check space in between for danger
                    if (tempBoard.board.at(kingrow - 1).at(0) != nullptr) 
                    {
                        delete tempBoard.board.at(kingrow - 1).at(0);
                    }

                    tempBoard.board.at(kingrow - 1).at(0) = tempPiece;
                    tempBoard.board.at(kingrow).at(kingcol) = nullptr;
                    tempPiece->setPosition(kingrow - 1, 0); // temp
                }
                king_safe = true;
            }
            else
            {
                king_safe = false;
            }

            if (king_safe == true)
            {
                // Castling check
                if (castle == false && castle_attempt == true)
                {
                    return(false);
                }
                return piece->canMoveToLocation(toRow, toCol);
            }
            else
            {
                return(false);
            }
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

    if (board.at(toRow).at(toCol) != nullptr) // if there is a piece there (isValidMove already checks for color)
    {
        delete board.at(toRow).at(toCol);
    }
    board.at(toRow).at(toCol) = pieceToMove;
    board.at(fromRow).at(fromCol) = nullptr;
    pieceToMove->setPosition(toRow, toCol);

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
                //if(isValidMove(i, j, row, col)) //piece can move to curr pos (under threat)
                if (piece->canMoveToLocation(row, col))
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