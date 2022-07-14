//
// Created by Azuolas on 7/12/2022.
//

#ifndef CHESS_ENGINE_LEGALITYTESTER_H
#define CHESS_ENGINE_LEGALITYTESTER_H

#include "ChessBoard.h"
#include "PseudoLegalMoveGenerator.h"

namespace ChessEngine
{
    class LegalityTester
    {
        PseudoLegalMoveGenerator plMoveGenerator;

        bool whiteThreatMap[8][8]; // squares attacked by white pieces
        bool blackThreatMap[8][8]; // squares attacked by black pieces


        bool isSquareAttacked(int x, int y);
    };
}



#endif //CHESS_ENGINE_LEGALITYTESTER_H
