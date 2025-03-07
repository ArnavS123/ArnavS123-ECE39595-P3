#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::ChessPiece;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column) : board(board), color(color), row(row), column(column)
{
}

Color ChessPiece::getColor() 
{
    return color;
}

int ChessPiece::getRow() 
{
    return row;
}

int ChessPiece::getColumn() 
{
    return column;
}

void ChessPiece::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}