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

void Print2darray(bool array[8][8]);
MoveType GetMoveTypeFromChar(char c);

int main() {
    FenParser fenParser;
    vector<MovePositionInfo> moveList;

    InitializeZobrist();
    bool isPlaying = false;

    Position* position = fenParser.loadFen(fenParser.startingFenString); // "r1bq1rk1/ppbn2pp/2p1pn2/3pNp2/3P1B2/4P2P/PPPNBPP1/R2Q1RK1 w - - 9 10"
    ChessBoard* board = position->board;
    MoveGenerator* moveGenerator = new MoveGenerator(position);
    Evaluator* evaluator = new Evaluator(position);
    Searcher* searcher = new Searcher(evaluator, moveGenerator);
    //TranspositionTable* tt = new TranspositionTable(position);

    //tt->ClearTable();
    //cout << NOT_FOUND;
//    for(int i = 0; i< 10; i++)
//    {
//        cout << GetRandomU64Number() << '\n';
//    }
    //cout << position->zobristKey << '\n';
    //board->PrintBoard();
    //cout << -(INT_MAX) << '\n';
//    auto start  = std::chrono::steady_clock::now();
//    cout << Perft(6, position, moveGenerator) << '\n';
//    auto end = std::chrono::steady_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end-start;
//    cout << "TIME: " << elapsed_seconds.count() << '\n';
    for(int i = 0; i < 2; i++)
    {
        auto start  = std::chrono::steady_clock::now();
        //cout << Perft(6, position, moveGenerator) << '\n';
        cout << searcher->posEvaluated << " " << searcher->transposFound << " " << searcher->tt->times << " " << searcher->tt->otherTimes << '\n';
        cout << searcher->Search(7, INT_MIN + 9999, INT_MAX - 9999) << " " << searcher->posEvaluated << " " << searcher->transposFound << " " << searcher->tt->times << " " << searcher->tt->otherTimes << '\n';
        searcher->posEvaluated = 0;
        searcher->tt->times = 0;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        cout << "TIME: " << elapsed_seconds.count() << '\n';
    }
//    std::vector<Move> moves = moveGenerator->GenerateAllCaptureMoves();
//    for (auto & move : moves)
//    {
//        cout << MoveToString(move) << '\n';
//    }
//    cout << moves.size() << "  ";
    //cout << "VALUE: " << GetPieceSquareValue(2, 5, KNIGHT, BLACK) << endl;
    while(isPlaying)
    {
//        tt->RecordEntry(Move(), evaluator->EvaluatePosition(), 1, 0);
        //cout << tt->ReadHashEntry(0, -1, 1) << '\n';
        //moveGenerator->GenerateAllMoves(WHITE);
        //moveGenerator->GetCheckRayMap();
        //Print2darray(moveGenerator->captureCheckMap);
        //cout << evaluator->EvaluatePosition() << '\n';
        //cout << searcher->Search(3) << '\n';
        if(position->activePlayerColor == BLACK)
        {
            searcher->Search(5, INT_MIN + 9000, INT_MAX-9000);
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
