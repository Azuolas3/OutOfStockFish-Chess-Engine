//
// Created by Azuolas on 1/11/2023.
//

#ifndef CHESS_ENGINE_PERFTUTILITY_H
#define CHESS_ENGINE_PERFTUTILITY_H

#include <iostream>
#include <fstream>
#include "Utilities/AlgebraicNotationUtility.h"
#include "MoveGenerator/MoveGenerator.h"
#include "BoardRepresentation/Position.h"
#include "Miscellaneous/u64.h"

namespace ChessEngine
{
    // bulk counting is a little "cheat" used to increase performance for perft
    u64 Perft(int depth, Position *position, MoveGenerator *moveGenerator, bool isBulkCountingEnabled = false); // generates and adds up all possible generated moves to a certain depth
}


#endif //CHESS_ENGINE_PERFTUTILITY_H
