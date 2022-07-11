//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_FENPARSER_H
#define CHESS_ENGINE_FENPARSER_H

#include <string>
#include <map>
#include "ChessBoard.h"
#include "pieces.h"
#include "Position.h"
#include "AlgebraicNotationUtility.h"

namespace ChessEngine
{
    class FenParser
    {
        std::map<char, ChessEngine::PieceType> pieceTypeMap =
        {
                {'p', ChessEngine::PAWN},
                {'b', ChessEngine::BISHOP},
                {'n', ChessEngine::KNIGHT},
                {'r', ChessEngine::ROOK},
                {'q', ChessEngine::QUEEN},
                {'k', ChessEngine::KING}
        };

    public:
        std::string const startingFenString = "rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d5 0 1";
        Position* loadFen(std::string fenString);
    };
}

#endif //CHESS_ENGINE_FENPARSER_H
