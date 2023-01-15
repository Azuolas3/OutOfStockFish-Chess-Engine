#include <iostream>
#include <vector>
#include <chrono>
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
MoveType GetMoveTypeFromChar(char c);

int main() {
    FenParser fenParser;
    vector<MovePositionInfo> moveList;

    bool isPlaying = true;

    Position* position = fenParser.loadFen(fenParser.startingFenString); // 8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - 0 1
    ChessBoard* board = position->board;
    MoveGenerator* moveGenerator = new MoveGenerator(position);


    board->PrintBoard();
    auto start  = std::chrono::steady_clock::now();
    cout << Perft(4, position, moveGenerator) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "TIME: " << elapsed_seconds.count();
    while(isPlaying)
    {
        //moveGenerator->GenerateAllMoves(WHITE);
        //moveGenerator->GetCheckRayMap();
        //Print2darray(moveGenerator->captureCheckMap);

        string moveInput;
        cin >> moveInput;
        if(moveInput == "STOP")
            break;
        else if(moveInput == "UNMAKE")
        {
            position->UndoMove(moveList.back());
            moveList.pop_back();
            board->PrintBoard();
            continue;
        }


        cout<<"MOVE START :" << position->activePlayerColor << endl;

        int startX = letterToFile(moveInput[0]);
        int startY = intToRank(moveInput[1]);

        int endX = letterToFile(moveInput[2]);
        int endY = intToRank(moveInput[3]);

        Move currentMove = Move(startX, startY, endX, endY);

        if(moveInput.length() >= 6)
        {
            char promotionPiece;
            promotionPiece = moveInput[5];
            currentMove.moveType = GetMoveTypeFromChar(promotionPiece);
        }

        vector<Move> generatedMoves;
        vector<Move> additionalMoves;


        //generatedMoves = moveGenerator->GeneratePieceMoves(board->pieces[startX][startY], startX, startY);
        generatedMoves = moveGenerator->GenerateAllMoves();
        cout << "number of moves   " << generatedMoves.size() << '\n';
        //cout << position->enPassantSquareX <<  " " << position->enPassantSquareY << endl;

        Move pseudoLegalMove;
        if(moveGenerator->plMoveGenerator->DoesContainMove(generatedMoves, currentMove, &pseudoLegalMove))
        {
            moveList.push_back(position->GenerateMoveInfo(pseudoLegalMove)); // add new move to list
            position->MakeMove(pseudoLegalMove);

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

MoveType GetMoveTypeFromChar(char c)
{
    switch(c)
    {
        case 'B':
            return B_PROMOTION;
        case 'N':
            return N_PROMOTION;
        case 'R':
            return R_PROMOTION;
        case 'Q':
            return Q_PROMOTION;
    }
}
