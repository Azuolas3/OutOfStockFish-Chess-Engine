#include <iostream>
#include <vector>
#include "pieces.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"
#include "AlgebraicNotationUtility.h"

using namespace ChessEngine;
using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;


int main() {
    Piece test[8][8] = { EMPTY };
    FenParser fenParser;

    Position* position = fenParser.loadFen(fenParser.startingFenString);
    ChessBoard* board = position->board;
    MoveGenerator* moveGenerator = new MoveGenerator(position);

    board->PrintBoard();
    while(true)
    {
        cout << moveGenerator->GenerateAllMoves(WHITE).size();

        string moveInput;
        cin >> moveInput;
        if(moveInput == "STOP")
            break;


        cout<<"MOVE START :" << IsKingsideEmpty(WHITE, board->pieces) << " " << position->HasCastlingRights(WHITE, KINGSIDE) << endl;

        int startX = letterToFile(moveInput[0]);
        int startY = intToRank(moveInput[1]);

        int endX = letterToFile(moveInput[2]);
        int endY = intToRank(moveInput[3]);

        vector<Move> generatedMoves;
        vector<Move> additionalMoves;

        generatedMoves = moveGenerator->GeneratePieceMoves(board->pieces[startX][startY], startX, startY);

        Move pseudoLegalMove;
        if(moveGenerator->plMoveGenerator->doesContainMove(generatedMoves, endX, endY, &pseudoLegalMove))
        {
            PieceList* pieceList = (getColor(board->pieces[startX][startY]) == WHITE) ? board->whitePieces : board->blackPieces;
            pieceList->MovePiece(startX, startY, endX, endY);
            board->MovePiece(startX, startY, endX, endY);
            moveGenerator->InitThreatMaps(*board);

            if(pseudoLegalMove.additionalAction != nullptr)
                pseudoLegalMove.additionalAction();

            position->activePlayerColor = (position->activePlayerColor == WHITE) ? BLACK : WHITE;

            board->PrintBoard();
        }

    }
    //cout << position->enPassantSquareX << " " << position->enPassantSquareY << endl;
    //generatedMoves = moveGenerator.GenerateStraightMoves(0, 0);
    //std::cout << "HELLO WORLD BLET " << test[2][0] << std::endl;

    //board->PrintBoard();

    /*for(int i = 0; i < generatedMoves.size(); i++)
    {
        cout << generatedMoves[i].destinationX << " " << generatedMoves[i].destinationY << endl;
    }*/

    return 0;
}

