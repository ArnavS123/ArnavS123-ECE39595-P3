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

void unit_isValidMove_bishop_one() {
    Student::ChessBoard board(4, 4);
    board.createChessPiece(White, Bishop, 0, 0);
    board.createChessPiece(Black, Bishop, 1, 1);
    board.createChessPiece(Black, Bishop, 0, 3);
    // assert(board.isValidMove(0, 0, 3, 3));
    // assert(!board.isValidMove(0, 0, 1, 2));
    // assert(!board.isValidMove(0, 0, -1, -1));
    std::cout << board.displayBoard().str();
    assert(board.movePiece(0, 0, 1, 1));
    assert(!(board.isPieceUnderThreat(1, 1)));
    std::cout << board.displayBoard().str();
    assert(board.movePiece(0, 3, 1, 2));
    std::cout << board.displayBoard().str();
    assert(board.movePiece(1, 1, 2, 2));
    std::cout << board.displayBoard().str();
}

void something()
{
    Student::ChessBoard sBoard(4, 4);

    // Creating chess pieces
    sBoard.createChessPiece(Black, Bishop, 0, 3);
    sBoard.createChessPiece(Black, Rook, 0, 3);
    sBoard.createChessPiece(White, Pawn, 2, 3);
    sBoard.createChessPiece(Black, Pawn, 3, 0);
    sBoard.createChessPiece(Black, King, 1, 2);
    sBoard.createChessPiece(White, King, 1, 0);
    
    std::cout << sBoard.displayBoard().str();

    // Moving pieces
    sBoard.movePiece(2, 3, 1, 3);
    std::cout << sBoard.displayBoard().str();
    sBoard.movePiece(0, 3, 0, 2);
    sBoard.movePiece(1, 0, 2, 0);
    sBoard.movePiece(0, 2, 0, 3);
    sBoard.movePiece(0, 0, 3, 3);
    sBoard.movePiece(2, 0, 3, 1);
    sBoard.movePiece(1, 2, 2, 3);
    sBoard.movePiece(3, 1, 2, 0);
    sBoard.movePiece(2, 3, 3, 3);
    sBoard.movePiece(2, 3, 1, 2);
    sBoard.movePiece(2, 0, 3, 1);
    sBoard.movePiece(0, 3, 0, 1);
    sBoard.movePiece(3, 1, 2, 0);
    sBoard.movePiece(0, 1, 0, 3);
    sBoard.movePiece(0, 0, 0, 1);
    sBoard.movePiece(2, 0, 3, 0);
    sBoard.movePiece(0, 3, 0, 2);
    sBoard.movePiece(3, 0, 2, 0);
    sBoard.movePiece(0, 2, 1, 2);
    sBoard.movePiece(2, 2, 3, 1);
    sBoard.movePiece(2, 0, 3, 0);
    sBoard.movePiece(3, 3, 2, 3);
    sBoard.movePiece(3, 0, 2, 0);
    sBoard.movePiece(2, 3, 2, 2);
    sBoard.movePiece(1, 1, 3, 1);
    sBoard.movePiece(2, 0, 3, 0);
    sBoard.movePiece(2, 2, 1, 3);
    sBoard.movePiece(3, 0, 3, 1);
    sBoard.movePiece(1, 3, 2, 3);
    sBoard.movePiece(0, 0, 1, 3);
    sBoard.movePiece(3, 1, 2, 0);
    sBoard.movePiece(2, 3, 3, 3);
    sBoard.movePiece(2, 0, 3, 1);
    sBoard.movePiece(3, 3, 2, 3);
    sBoard.movePiece(2, 2, 1, 0);
    sBoard.movePiece(3, 1, 2, 1);
    sBoard.movePiece(1, 2, 3, 2);
    sBoard.movePiece(2, 1, 2, 0);
    sBoard.movePiece(3, 2, 2, 2);
    sBoard.movePiece(0, 1, 0, 0);
    sBoard.movePiece(2, 0, 1, 0);
    sBoard.movePiece(2, 2, 3, 2);
    sBoard.movePiece(1, 0, 2, 0);
    sBoard.movePiece(3, 2, 3, 1);
    sBoard.movePiece(3, 2, 0, 3);
    sBoard.movePiece(2, 0, 3, 1);
    sBoard.movePiece(2, 3, 3, 3);
    sBoard.movePiece(3, 1, 2, 0);
    sBoard.movePiece(3, 3, 3, 2);
    sBoard.movePiece(1, 2, 3, 1);
    sBoard.movePiece(2, 0, 1, 0);
    sBoard.movePiece(3, 2, 3, 3);
    sBoard.movePiece(1, 0, 0, 0);
    sBoard.movePiece(3, 3, 3, 2);
    sBoard.movePiece(0, 3, 0, 1);
    sBoard.movePiece(0, 0, 1, 1);
    sBoard.movePiece(3, 2, 3, 1);
    sBoard.movePiece(1, 1, 0, 0);
    sBoard.movePiece(3, 1, 2, 0);
    sBoard.movePiece(2, 3, 1, 0);
    sBoard.movePiece(0, 0, 0, 1);
    sBoard.movePiece(2, 0, 3, 0);
    sBoard.movePiece(0, 1, 1, 2);
    sBoard.movePiece(3, 0, 2, 0);
    
    std::cout << sBoard.displayBoard().str();
}

int main()
{
    something();//unit_isValidMove_bishop_one();
    return EXIT_SUCCESS;
}