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

        char line[INPUT_BUFFER];

        while(true)
        {
            memset(line, 0, sizeof(line[0]) * INPUT_BUFFER);
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

    }

    void ParsePosition(std::string input, Position *position)
    {
        FenParser parser;
        int currentPos = 0;

        std::string arguments = input.substr(9); // starting at 9 since we can safely skip "position " part of the string
        if(arguments == "startpos")
        {
            position = parser.loadFen(parser.startingFenString);
        }
        else
        {
            currentPos = arguments.find("fen");
            if(currentPos != std::string::npos)
            {
                std::string fenString = arguments.substr(currentPos + 4);
                position = parser.loadFen(fenString);
            }
            else
            {
                position = parser.loadFen(parser.startingFenString);
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

        position->board->PrintBoard();
    }
}