//
// Created by Azuolas on 7/5/2022.
//

#include "FenParser.h"

using namespace ChessEngine;

Position* FenParser::loadFen(std::string fenString)
{
    Position* position = new Position();
    position->board = new ChessBoard();

    int x = 0, y = 7;
    int charIterator = 0;
    for (char& currChar : fenString)
    {
        charIterator++;
        if(std::isdigit(currChar))
        {
            x += currChar - 48; // turning from ascii char to int;
            continue;
        }

        if(currChar == '/')
        {
            x = 0;
            y--;
            continue;
        }

        ChessEngine::PieceType pieceType = pieceTypeMap[tolower(currChar)];
        ChessEngine::Color pieceColor;

        if(std::islower(currChar))
            pieceColor = ChessEngine::BLACK;
        else
            pieceColor = ChessEngine::WHITE;

        //std::cout << (pieceColor | pieceType) << std::endl;
        ChessEngine::Piece piece = static_cast<ChessEngine::Piece>(pieceColor | pieceType);
        position->board->pieces[x][y] = piece;
        x++;

        if(currChar == ' ')
            break;
    }

    charIterator++; //Skip empty character and move to color specifier

    if(fenString[charIterator] == 'w')
    {
        position->activePlayerColor = WHITE;
    }
    else
    {
        position->activePlayerColor = BLACK;
    }

    charIterator += 2; // Skip empty char and move to castling rights specifier
    std::string fenSubString = fenString.substr(charIterator-1);

    if(fenSubString.find('K') != std::string::npos)
    {
        charIterator++;
        position->whiteCastlingRights = static_cast<CastlingRights>(position->whiteCastlingRights | KINGSIDE);
    }

    if(fenSubString.find('Q') != std::string::npos)
    {
        charIterator++;
        position->whiteCastlingRights = static_cast<CastlingRights>(position->whiteCastlingRights | QUEENSIDE);
    }

    if(fenSubString.find('K') != std::string::npos)
    {
        charIterator++;
        position->blackCastlingRights = static_cast<CastlingRights>(position->blackCastlingRights | KINGSIDE);
    }

    if(fenSubString.find('Q') != std::string::npos)
    {
        charIterator++;
        position->blackCastlingRights = static_cast<CastlingRights>(position->blackCastlingRights | QUEENSIDE);
    }

    if(charIterator != '-')
    {
        // code for en passant square but fk that shit
    }

    charIterator += 2;

    position->fiftyMoveRuleCounter = std::stoi(&fenString[charIterator]);

    return position;
}
