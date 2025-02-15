#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <memory>
#include <vector>
#include "Pieces/piece.h"
#include "Pieces/bishop.h"
#include "Pieces/blankPiece.h"
#include "Pieces/king.h"
#include "Pieces/knight.h"
#include "Pieces/pawn.h"
#include "Pieces/queen.h"
#include "Pieces/rook.h"

const size_t BOARD_SIZE = 8;

class Board {
  private: 
    std::vector<std::vector<std::unique_ptr<Piece>>> chessBoard;

  public:
    Board();
    ~Board();
    Piece* getPiece(int row, int col);
    char charAt(int row, int col);
    void createStartingBoard();
    void createEmptyBoard();
    void setPiece(int row, int col); //probably change this to take in a piece pointer
    void unSetPiece(int row, int col); //probably change this to return a piece pointer
    void makeMove(int startRow, int startCol, int endRow, int endCol);
    bool isValidMove(bool isWhitePLayer, size_t startRow, size_t startCol, size_t endRow, size_t endCol);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();

};

#endif
