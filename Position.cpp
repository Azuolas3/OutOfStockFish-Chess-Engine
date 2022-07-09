//
// Created by Azuolas on 7/9/2022.
//

#include "Position.h"
using namespace ChessEngine;

void Position::RemoveCastlingRights(PieceColor color, CastlingRights side)
{
    CastlingRights* sideRights = (color == WHITE) ? &whiteCastlingRights : &blackCastlingRights;

    *sideRights = static_cast<CastlingRights>(*sideRights & ~side);
}
