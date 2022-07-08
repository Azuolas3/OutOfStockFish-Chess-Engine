#include <iostream>
#include <vector>
#include "pieces.h"
#include "FenParser.h"
#include "MoveGenerator.h"

using namespace ChessEngine;
using std::cout; using std::endl;
using std::vector;


int main() {
    Piece test[8][8] = { EMPTY };
    vector<Move> generatedMoves;
    FenParser fenParser;

    Position position = fenParser.loadFen(fenParser.startingFenString);
    ChessBoard board = position.board;
    MoveGenerator moveGenerator(board);
    //cout << board.pieces[0][0] << endl;
    generatedMoves = moveGenerator.GeneratePawnMoves(4, 5);
    //std::cout << "HELLO WORLD BLET " << test[2][0] << std::endl;

    board.printBoard();

/*    for(int i = 0; i < generatedMoves.size(); i++)
    {
        cout << generatedMoves[i].destinationX << " " << generatedMoves[i].destinationY << endl;
    }*/

    //if(position.whiteKingCastlingRights)
/*    cout << position.whiteKingCastlingRights << " " << position.whiteQueenCastlingRights << " " << position.blackKingCastlingRights << " " << position.blackQueenCastlingRights << endl;
    cout << position.fiftyMoveRuleCounter;*/

    return 0;
}

