//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_FENPARSER_H
#define CHESS_ENGINE_FENPARSER_H

#include <string>
#include <map>
#include "BoardRepresentation/ChessBoard.h"
#include "BoardRepresentation/pieces.h"
#include "BoardRepresentation/Position.h"
#include "Utilities/AlgebraicNotationUtility.h"
#include "Utilities/ZobristUtility.h"

namespace ChessEngine
{
    class FenParser
    {
        std::map<char, ChessEngine::PieceType> pieceTypeMap = // for parsing fen
        {
                {'p', ChessEngine::PAWN},
                {'b', ChessEngine::BISHOP},
                {'n', ChessEngine::KNIGHT},
                {'r', ChessEngine::ROOK},
                {'q', ChessEngine::QUEEN},
                {'k', ChessEngine::KING}
        };

    public:
        std::string const startingFenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        Position* ParseFen(std::string fenString);
    };
}

#endif //CHESS_ENGINE_FENPARSER_H
