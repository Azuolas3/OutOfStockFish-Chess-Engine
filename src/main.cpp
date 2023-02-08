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
#include "Evaluator.h"
#include "Searcher.h"
#include "ZobristUtility.h"
#include "TranspositionTable.h"

using namespace ChessEngine;
using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;

MoveType GetMoveTypeFromChar(char c);

int main() {
    FenParser fenParser;
    vector<MovePositionInfo> moveList;

    InitializeZobrist();
    bool isPlaying = true;

    Position* position = fenParser.loadFen(fenParser.startingFenString); // "r1bq1rk1/ppbn2pp/2p1pn2/3pNp2/3P1B2/4P2P/PPPNBPP1/R2Q1RK1 w - - 9 10"
    ChessBoard* board = position->board;
    MoveGenerator* moveGenerator = new MoveGenerator(position);
    Evaluator* evaluator = new Evaluator(position);
    Searcher* searcher = new Searcher(evaluator, moveGenerator);

//    for(int i = 0; i< 10; i++)
//    {
//        cout << GetRandomU64Number() << '\n';
//    }

    auto start  = std::chrono::steady_clock::now();
    cout << searcher->Search(1, INT_MIN + 9999, INT_MAX - 9999) << " " << searcher->posEvaluated << " " << searcher->transposFound << " " << searcher->tt->times << " " << searcher->tt->otherTimes << '\n';
    cout << MoveToString(searcher->currentBestMove) << '\n';
     auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "TIME: " << elapsed_seconds.count() << '\n';

    while(isPlaying)
    {
        if(position->activePlayerColor == BLACK)
        {
            cout << "eval:   " << searcher->SearchIteratively(2) << '\n';
            //searcher->Search(6, INT_MIN + 9999, INT_MAX - 9999);
            position->MakeMove(searcher->currentBestMove);
            cout << MoveToString(searcher->currentBestMove) << '\n';
        }

        board->PrintBoard();
        string moveInput;
        cin >> moveInput;
        if(moveInput == "STOP")
            break;
        else if(moveInput == "UNMAKE")
        {
            position->UndoMove(moveList.back());
            moveList.pop_back();
            //board->PrintBoard();
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
        generatedMoves = moveGenerator->GenerateAllMoves(NORMAL);
        cout << "number of moves   " << generatedMoves.size() << '\n';
        //cout << position->enPassantSquareX <<  " " << position->enPassantSquareY << endl;

        Move pseudoLegalMove;
        if(moveGenerator->plMoveGenerator->DoesContainMove(generatedMoves, currentMove, &pseudoLegalMove))
        {
            moveList.push_back(position->GenerateMoveInfo(pseudoLegalMove)); // add new move to list
            position->MakeMove(pseudoLegalMove);

            cout << "\n MOVED SUCCESSFULLY \n";
            //cout << "\n" << position->board->whitePieces->count << "\n";
        }

    }

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


