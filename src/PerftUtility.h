//
// Created by Azuolas on 1/11/2023.
//

#ifndef CHESS_ENGINE_PERFTUTILITY_H
#define CHESS_ENGINE_PERFTUTILITY_H

#include <iostream>
#include <fstream>
#include "AlgebraicNotationUtility.h"
#include "MoveGenerator.h"
#include "Position.h"

namespace ChessEngine
{
    typedef unsigned long long u64;

    u64 Perft(int depth, Position *position, MoveGenerator *moveGenerator, bool isBulkCountingEnabled = false); // generates and adds up all possible generated moves to a certain depth
}


#endif //CHESS_ENGINE_PERFTUTILITY_H
