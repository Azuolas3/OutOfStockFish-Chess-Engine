#include <iostream>
#include <vector>
#include "pieces.h"
#include "Move.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"
#include "AlgebraicNotationUtility.h"
#include "PerftUtility.h"

using namespace ChessEngine;
using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;

void Print2darray(bool array[8][8]);

int main() {
    FenParser fenParser;
    vector<MovePositionInfo> moveList;

    bool isPlaying = true;

    Position* position = fenParser.loadFen("r1bqkbnr/ppp1pppp/2q5/8/B7/4P3/PPPP1PPP/RNBQK1NR w KQkq - 1 2");
    ChessBoard* board = position->board;
    MoveGenerator* moveGenerator = new MoveGenerator(position);


    board->PrintBoard();
    //cout << Perft(1, position, moveGenerator);
    while(isPlaying)
    {
        //moveGenerator->GenerateAllMoves(WHITE);
        //moveGenerator->GetCheckRayMap();
        //Print2darray(moveGenerator->captureCheckMap);

        string moveInput;
        cin >> moveInput;
        if(moveInput == "STOP")
            break;


        cout<<"MOVE START :" << position->activePlayerColor << endl;

        int startX = letterToFile(moveInput[0]);
        int startY = intToRank(moveInput[1]);

        int endX = letterToFile(moveInput[2]);
        int endY = intToRank(moveInput[3]);

        Move currentMove = Move(startX, startY, endX, endY);

        vector<Move> generatedMoves;
        vector<Move> additionalMoves;


        //generatedMoves = moveGenerator->GeneratePieceMoves(board->pieces[startX][startY], startX, startY);
        generatedMoves = moveGenerator->GenerateAllMoves();
        cout << "number of moves   " << generatedMoves.size() << '\n';
        //cout << position->enPassantSquareX <<  " " << position->enPassantSquareY << endl;

        Move pseudoLegalMove;
        if(moveGenerator->plMoveGenerator->doesContainMove(generatedMoves, Square(startX, startY), Square(endX, endY), &pseudoLegalMove))
        {
            board->MovePiece(currentMove);

            position->enPassantSquareX = -1;
            position->enPassantSquareY = -1;

            if(pseudoLegalMove.additionalAction != nullptr)
                pseudoLegalMove.additionalAction();

            position->activePlayerColor = (position->activePlayerColor == WHITE) ? BLACK : WHITE;

            moveGenerator->InitThreatMaps();

            board->PrintBoard();
            cout << "\n MOVED SUCCESSFULLY \n";
            //cout << "\n" << position->board->whitePieces->count << "\n";
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

void Print2darray(bool array[8][8])
{
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            if(array[j][i])
                cout<<"1 ";
            else
                cout<<"0 ";
        }
        std::cout << std::endl;
    }
}

