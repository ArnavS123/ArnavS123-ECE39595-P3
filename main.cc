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
    Student::ChessBoard board(8, 8);

    // Create kings
    board.createChessPiece(White, King, 7, 4);
    board.createChessPiece(Black, King, 0, 4);

    // Create rooks for castling
    board.createChessPiece(White, Rook, 7, 0);
    board.createChessPiece(White, Rook, 7, 7);
    board.createChessPiece(Black, Rook, 0, 0);
    board.createChessPiece(Black, Rook, 0, 7);

    // Move white king to right (castling prep)
    board.movePiece(7, 4, 7, 5);
    board.movePiece(0, 0, 1, 0);
    board.movePiece(7, 5, 7, 4);
    board.movePiece(1, 0, 2, 0);

    // Move black rook to open path
    board.movePiece(0, 7, 0, 6);
    board.movePiece(2, 0, 3, 0);

    // Perform castling
    board.movePiece(7, 4, 7, 6); // White castles kingside
    board.movePiece(0, 4, 0, 2); // Black castles queenside (test both sides!)

    std::cout << board.displayBoard().str();

    // After this function ends:
    // --> board and copiedBoard destructors will run
    // --> All pieces should be deleted without leaks
}

int main()
{
    something();
    return EXIT_SUCCESS;
}