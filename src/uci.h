//
// Created by Azuolas on 2/15/2023.
//

#ifndef CHESS_ENGINE_UCI_H
#define CHESS_ENGINE_UCI_H

#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "BoardRepresentation/Position.h"
#include "Miscellaneous/FenParser.h"
#include "AI/Searcher.h"

namespace ChessEngine
{
    void UciLoop();
    void ParseGo(std::string input, Position* position);
    void ParsePosition(std::string input, Position *&position);
}

#endif //CHESS_ENGINE_UCI_H
