#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::ChessPiece;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column) : board(board), color(color), row(row), column(column)
{
}

Color ChessPiece::getColor() const
{
    return color;
}

int ChessPiece::getRow() const
{
    return row;
}

int ChessPiece::getColumn() const
{
    return column;
}

void ChessPiece::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}