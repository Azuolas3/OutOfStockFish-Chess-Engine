//
// Created by Azuolas on 2/15/2023.
//

#include "uci.h"

using std::string;
using std::cout; using std::cin;

namespace ChessEngine
{
    void UciLoop()
    {
        Position* position;

        while(true)
        {
            string input;
            std::getline(cin, input);

            if(input.empty())
                continue;

            std::string firstWord = input.substr(0, input.find(" "));
            if(input == "isready")
            {
                cout << "readyok\n";
                continue;
            }
            else if(firstWord == "position")
            {
                ParsePosition(input, position);
            }
            else if(firstWord == "ucinewgame")
            {
                ParsePosition("position startpos\n", position);
            }
            else if(firstWord == "go")
            {
                ParseGo(input, position);
            }
            else if(firstWord == "quit")
            {
                break;
            }
            else if(firstWord == "uci")
            {
                cout << "id name OutOfStockFish\n";
                cout << "id author Azuolas\n";
                cout << "uciok\n";
            }
        }
    }

    void ParseGo(std::string input, Position *position)
    {
        MoveGenerator* moveGenerator = new MoveGenerator(position);
        Evaluator* evaluator = new Evaluator(position);
        Searcher* searcher = new Searcher(evaluator, moveGenerator);

        int depth = - 1;
        int time = -1, inc = 0;
        int movesToGo = 30, moveTime = -1;

        int currentPos;

        currentPos = input.find("infinite");
        if(currentPos != std::string::npos)
            ;

        currentPos = input.find("winc");
        if(currentPos != std::string::npos && position->activePlayerColor == WHITE)
            inc = stoi(input.substr(currentPos + 5));

        currentPos = input.find("binc");
        if(currentPos != std::string::npos && position->activePlayerColor == BLACK)
            inc = stoi(input.substr(currentPos + 5));

        currentPos = input.find("wtime");
        if(currentPos != std::string::npos && position->activePlayerColor == WHITE)
            time = stoi(input.substr(currentPos + 6));

        currentPos = input.find("btime");
        if(currentPos != std::string::npos && position->activePlayerColor == BLACK)
            time = stoi(input.substr(currentPos + 6));

        currentPos = input.find("movestogo");
        if(currentPos != std::string::npos)
            movesToGo = stoi(input.substr(currentPos + 10));

        currentPos = input.find("movetime");
        if(currentPos != std::string::npos)
            moveTime = stoi(input.substr(currentPos + 9));

        currentPos = input.find("depth");
        if(currentPos != std::string::npos)
            depth = stoi(input.substr(currentPos + 6));

        if(moveTime != -1)
        {
            time = moveTime;
            movesToGo = 1;
        }

        if(time != -1)
        {
            time /= movesToGo;
            time -= 50; // 50ms smaller time just in case of going over it
        }

        if(depth == -1)
            searcher->maxDepth = MAX_DEPTH; // if depth is -1, that means search until you are stopped basically
        else
            searcher->maxDepth = depth;

        searcher->SearchIteratively((time + inc) / 1000); // divided by 1000 since search expects seconds and UCI expects ms

        delete evaluator; // clean up memory after search
        delete searcher;
        delete moveGenerator;

        cout << "bestmove " << MoveToString(searcher->currentBestMove) << '\n'; //send the best move found to GUI
    }

    void ParsePosition(std::string input, Position *&position)
    {
        FenParser parser;
        int currentPos = 0;

        std::string arguments = input.substr(9); // starting at 9 since we can safely skip "position " part of the string
        if(arguments == "startpos")
        {
            position = parser.ParseFen(parser.startingFenString);
        }
        else
        {
            currentPos = arguments.find("fen");
            if(currentPos != std::string::npos)
            {
                std::string fenString = arguments.substr(currentPos + 4);
                position = parser.ParseFen(fenString);
            }
            else
            {
                position = parser.ParseFen(parser.startingFenString);
            }
        }

        currentPos = arguments.find("moves");
        if(currentPos != std::string::npos)
        {
            std::string movesInput = arguments.substr(currentPos + 6);
            std::stringstream ss(movesInput);
            while(!ss.eof())
            {
                std::string moveString;
                ss >> moveString;
                Move parsedMove = StringToMove(moveString);
                position->MakeMove(parsedMove);
            }
        }

        //position->board->PrintBoard();
    }
}