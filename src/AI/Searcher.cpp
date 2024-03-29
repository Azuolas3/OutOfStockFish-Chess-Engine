//
// Created by Azuolas on 1/23/2023.
//

#include "Searcher.h"

namespace ChessEngine
{
    int Searcher::SearchIteratively(int allocatedSearchTime)
    {
        isSearchRunning = true;

        int currentDepth = 1; // start from 1 ply depth
        int latestEval = 0;

        auto future1 = std::async(StartTimer, allocatedSearchTime, [this] {EndSearch();});
        auto future2 = std::async(&Searcher::PeriodicInputCheck, this, 100);
        while(isSearchRunning && currentDepth <= maxDepth)
        {
            Move previousIterationBestMove = currentBestMove;
            int previousIterationEval = latestEval;

            latestEval = Search(currentDepth, -STARTING_VALUE, STARTING_VALUE);

            currentDepth++;

            if(!isSearchRunning) // in case allocated time ends before search is over, revert back to previous iteration's best move
            {
                currentBestMove = previousIterationBestMove;
                latestEval = previousIterationEval;
            }
        }

        return latestEval;
    }

    int Searcher::Search(int depth, int alpha, int beta)
    {
        if(!isSearchRunning)
            return 0;

        tt->times++;
        int ttLookup = tt->ReadHashEntryEval(depth, alpha, beta);

        if(ttLookup != NOT_FOUND)
        {
            transposFound++;
            currentBestMove = tt->ReadHashEntryMove();
            return ttLookup;
        }

        if (depth == 0)
            return QuiescenceSearch(alpha, beta);


        std::vector<Move> moveList = moveGenerator->GenerateAllMoves(NORMAL);

        if(moveList.empty()) // if you have 0 moves, its either checkmate or stalemate
        {
            if(moveGenerator->IsInCheck())
                return MATED; // worst possible eval for checkmate
            else
                return 0; // draw eval for stalemate
        }

        Move bestMove;
        int evalFlag = tt->alphaFlag;
        OrderMoves(moveList);
        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -Search(depth - 1, -beta, -alpha);
            position->UndoMove(moveInfo);

            if(currentEvaluation >= beta)
            {
                if(depth >= 2)
                    tt->RecordEntry(move, beta, depth, tt->betaFlag);

                return beta;
            }
            if(currentEvaluation > alpha)
            {
                evalFlag = tt->exactFlag;
                bestMove = move;
                alpha = currentEvaluation;
            }
        }

        currentBestMove = bestMove;

        if(depth >= 2)
            tt->RecordEntry(bestMove, alpha, depth, evalFlag);

        return alpha;
    }

    int Searcher::QuiescenceSearch(int alpha, int beta)
    {
        posEvaluated++;
        int standPat = evaluator->EvaluatePosition();

        if(standPat >= beta)
            return beta;

//        if(standPat < alpha - DELTA) //delta pruning
//        {
//            return alpha;
//        }

        if(standPat > alpha)
            alpha = standPat;


        std::vector<Move> moveList = moveGenerator->GenerateAllMoves(CAPTURE_ONLY);

        std::sort(moveList.begin(), moveList.end(), [this](const Move& a, const Move& b){return this->SortCaptures(a, b);});
        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -QuiescenceSearch(-beta, -alpha);
            position->UndoMove(moveInfo);

            if (currentEvaluation >= beta)
                return beta;
            if(currentEvaluation > alpha)
                alpha = currentEvaluation;
        }

        return alpha;
    }

    bool Searcher::SortMoves(const Move &firstMove, const Move &secondMove)
    {
        Move storedTTMove = tt->ReadHashEntryMove();

        if(firstMove == storedTTMove)
            return true;

        if(secondMove == storedTTMove)
            return false;

        int firstMoveCaptureValue = EvaluateCapture(firstMove);
        int secondMoveCaptureValue = EvaluateCapture(secondMove);

        return firstMoveCaptureValue < secondMoveCaptureValue;
    }

    bool Searcher::SortCaptures(const Move &firstMove, const Move &secondMove)
    {
        int firstMoveCaptureValue = EvaluateCapture(firstMove);
        int secondMoveCaptureValue = EvaluateCapture(secondMove);

        return firstMoveCaptureValue < secondMoveCaptureValue;
    }

    int Searcher::EvaluateCapture(const Move &capture)
    {
        PieceType startingPieceType = GetType(board->pieces[capture.startingX][capture.startingY]);
        PieceType capturedPieceType = GetType(board->pieces[capture.destinationX][capture.destinationY]);

        if(startingPieceType == 0 || capturedPieceType == 0) // in case of bug where a quiet move would be evaluated here
            return 0;

        int captureValue = pieceValueMap[startingPieceType] - pieceValueMap[capturedPieceType];
        return captureValue;
    }

    void Searcher::OrderMoves(std::vector<Move> &moveList)
    {
        std::sort(moveList.begin(), moveList.end(), [this](const Move& a, const Move& b){return this->SortMoves(a, b);});
    }

    void Searcher::EndSearch()
    {
        isSearchRunning = false;
    }

    bool Searcher::HasStopped()
    {
        return !isSearchRunning;
    }

    void Searcher::ReadInput()
    {
        int bytes;
        std::string input;
        int pos;

        if(ChessEngine::InputWaiting())
        {
            this->EndSearch();
            do
            {
                bytes = read(fileno(stdin), input.data(), 256);
            }
            while (bytes < 0);
            pos = input.find('\n');

            if(pos != std::string::npos)
                pos = 0;

            if(input.length() > 0)
            {
                pos = input.find("quit");
                if(pos != std::string::npos)
                    this->EndSearch();
            }
        }
    }

    void Searcher::PeriodicInputCheck(int ms)
    {
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            ReadInput();
            if(this->HasStopped())
                break;
        }
    }
} // ChessEngine