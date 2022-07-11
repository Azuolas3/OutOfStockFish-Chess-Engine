#include <iostream>
#include <vector>
#include "pieces.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"

using namespace ChessEngine;
using std::cout; using std::endl;
using std::vector;


int main() {
    Piece test[8][8] = { EMPTY };
    vector<Move> generatedMoves;
    FenParser fenParser;

    Position* position = fenParser.loadFen(fenParser.startingFenString);
    ChessBoard* board = position->board;
    MoveGenerator moveGenerator(position);
    cout << position->enPassantSquareX << " " << position->enPassantSquareY << endl;
    generatedMoves = moveGenerator.GeneratePawnMoves(4, 4);
    //std::cout << "HELLO WORLD BLET " << test[2][0] << std::endl;

    board->PrintBoard();

    for(int i = 0; i < generatedMoves.size(); i++)
    {
        cout << generatedMoves[i].destinationX << " " << generatedMoves[i].destinationY << endl;
    }

    //board->MovePiece(0, 0, 5, 3);
    generatedMoves[1].additionalAction();
    //board->RemovePiece(3, 4);
    //position->board->MovePiece(7, 7, 0, 5);

    board->PrintBoard();

    //if(position.whiteKingCastlingRights)
    cout << position->whiteCastlingRights << endl;
    //position.RemoveCastlingRights(WHITE, BOTH);
    cout << position->whiteCastlingRights << endl;
    //cout << IsKingsideEmpty(BLACK, board.pieces) << endl;

    return 0;
}

