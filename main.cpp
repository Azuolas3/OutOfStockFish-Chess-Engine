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

    ChessBoard board = fenParser.loadFen(fenParser.startingFenString);
    MoveGenerator moveGenerator(board);
    //cout << board.pieces[4][3] << endl;
    generatedMoves = moveGenerator.GeneratePawnMoves(4, 5);
    //std::cout << "HELLO WORLD BLET " << test[2][0] << std::endl;

    board.printBoard();

    for(int i = 0; i < generatedMoves.size(); i++)
    {
        cout << generatedMoves[i].destinationX << " " << generatedMoves[i].destinationY << endl;
    }

    return 0;
}

