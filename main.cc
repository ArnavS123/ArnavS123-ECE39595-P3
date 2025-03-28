#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.

    return;
}

void something()
{
    Student::ChessBoard sBoard(8, 8);
    sBoard.createChessPiece(White, Pawn, 2, 4);
    sBoard.createChessPiece(White, Bishop, 3, 6);
    sBoard.createChessPiece(Black, Bishop, 7, 3);
    sBoard.createChessPiece(Black, Pawn, 5, 1);
    sBoard.createChessPiece(White, Bishop, 7, 2);
    sBoard.createChessPiece(Black, Bishop, 2, 2);
    sBoard.createChessPiece(Black, Bishop, 7, 7);
    sBoard.createChessPiece(White, Bishop, 4, 2);
    sBoard.createChessPiece(Black, King, 0, 4);
    sBoard.createChessPiece(White, King, 7, 4);
    sBoard.createChessPiece(Black, Rook, 0, 0);
    sBoard.createChessPiece(Black, Rook, 0, 7);
    sBoard.createChessPiece(White, Rook, 7, 0);
    sBoard.createChessPiece(White, Rook, 7, 7);

    std::cout << sBoard.displayBoard().str();
}

int main()
{
    something();
    return EXIT_SUCCESS;
}