#include "board.h"

Board::Board() 
{
    createEmptyBoard();
};

Board::~Board(){

};

void Board::createStartingBoard()
{
    if (chessBoard.size() != 0){
        chessBoard.clear();      
    }

    //row 0
    chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
    chessBoard[0].push_back(std::make_unique<Rook>(false));
    chessBoard[0].push_back(std::make_unique<Knight>(false));
    chessBoard[0].push_back(std::make_unique<Bishop>(false));
    chessBoard[0].push_back(std::make_unique<Queen>(false));
    chessBoard[0].push_back(std::make_unique<King>(false));
    chessBoard[0].push_back(std::make_unique<Bishop>(false));
    chessBoard[0].push_back(std::make_unique<Knight>(false));
    chessBoard[0].push_back(std::make_unique<Rook>(false));

    //row 1
    chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
    for (size_t j = 0; j < BOARD_SIZE; j++){
        chessBoard[1].push_back(std::make_unique<Pawn>(false));
    }

    //initalize blankPieces
    for (size_t i = 2; i < 6; i++){
        chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
        for (size_t j = 0; j < BOARD_SIZE; j++){
            chessBoard[i].push_back(std::make_unique<BlankPiece>(true));
        }
    }

    //row 6
    chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
    for (size_t j = 0; j < BOARD_SIZE; j++){
        chessBoard[6].push_back(std::make_unique<Pawn>(true));
    }

    //row 7
    chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
    chessBoard[7].push_back(std::make_unique<Rook>(true));
    chessBoard[7].push_back(std::make_unique<Knight>(true));
    chessBoard[7].push_back(std::make_unique<Bishop>(true));
    chessBoard[7].push_back(std::make_unique<Queen>(true));
    chessBoard[7].push_back(std::make_unique<King>(true));
    chessBoard[7].push_back(std::make_unique<Bishop>(true));
    chessBoard[7].push_back(std::make_unique<Knight>(true));
    chessBoard[7].push_back(std::make_unique<Rook>(true));

};

void Board::createEmptyBoard()
{
    if (chessBoard.size() != 0){
        chessBoard.clear();      
    }

    for (size_t i = 0; i < BOARD_SIZE; i++){
        chessBoard.push_back(std::vector <std::unique_ptr<Piece>>());
        for (size_t j = 0; j < BOARD_SIZE; j++){
            chessBoard[i].push_back(std::make_unique<BlankPiece>(true));
        }
    }
};

//returns a RAW pointer. 
//why? You should always use a raw pointer if you're not modifying ownership.
Piece* Board::getPiece(int row, int col)
{
    return chessBoard[row][col].get();
};

char Board::charAt(int row, int col)
{
    return getPiece(row, col)->charAt(row, col);
};

void Board::setPiece(int row, int col)
{
    return;
}

void Board::unSetPiece(int row, int col)
{
    return;
}

//not finished yet
void Board::makeMove(int startRow, int startCol, int endRow, int endCol)
{
    unSetPiece(startRow, startCol); //this should return a piece pointer
    setPiece(endRow, endCol); //pass in the piece pointer that was returned above
}

//Board::isValidMove()
// check all the conditions that are common for checking every valid move, which include:
//1. Check that starting piece is the players piece
//2. Check boundaries
//3. Check that end piece is NOT the players piece (they can't kill themselves)
//after all these conditions are checked, then check for individual piece moveablity

bool Board::isValidMove(bool isWhitePlayer, size_t startRow, size_t startCol, size_t endRow, size_t endCol)
{
    //check boundaries 
    if (startRow < 0 || startCol < 0 || endRow >= BOARD_SIZE || endCol >= BOARD_SIZE)
    {
        return false;
    };

    //check if no move was made 
    if (startRow == endRow && startCol == endCol)
    {
        return false;
    }

    //check if the start piece is blank
    if (charAt(startRow, startCol) == ' ')
    {
        return false;
    }

    //check if white player turn, but is trying to move black piece
    if (isWhitePlayer && !getPiece(startRow, startCol)->isWhite())
    {
        return false;
    }
    //check if black player turn, but is trying to move white piece
    if (!isWhitePlayer && getPiece(startRow, startCol)->isWhite())
    {
        return false;
    }

    //check if the player is trying to kill themselves
    if (isWhitePlayer == getPiece(endRow, endCol)->isWhite() && charAt(endRow, endCol) != ' ')
    {
        return false;
    } 

    //check if the player is trying to kill a king
    if (charAt(endRow, endCol) == 'K' || charAt(endRow, endCol) == 'k')
    {
        return false;
    }

    return getPiece(startRow, startCol)->isValidMove(startRow, startCol, endRow, endCol);

};

bool Board::isCheck()
{
    return true;
};

bool Board::isCheckmate()
{
    return true;
};

bool Board::isStalemate()
{
    return true;
};

