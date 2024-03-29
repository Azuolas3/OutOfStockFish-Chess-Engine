//
// Created by Azuolas on 7/5/2022.
//

#include "FenParser.h"

using namespace ChessEngine;

Position* FenParser::ParseFen(std::string fenString)
{
    Position* position = new Position();
    position->board = new ChessBoard();

    int x = 0, y = 7;
    int charIterator = 0;

    // Parse pieces
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

        if(currChar == ' ')
            break;

        ChessEngine::PieceType pieceType = pieceTypeMap[tolower(currChar)];
        ChessEngine::Color pieceColor;

        if(std::islower(currChar))
            pieceColor = ChessEngine::BLACK;
        else
            pieceColor = ChessEngine::WHITE;

        Piece piece = static_cast<Piece>(pieceColor | pieceType);
        position->board->pieces[x][y] = piece;

        if(piece == W_KING)
        {
            position->board->whiteKingX = x;
            position->board->whiteKingY = y;
        }
        if(piece == B_KING)
        {
            position->board->blackKingX = x;
            position->board->blackKingY = y;
        }

        if(pieceColor == WHITE)
            position->board->whitePieces->AddPiece(x, y);
        if(pieceColor == BLACK)
            position->board->blackPieces->AddPiece(x, y);

        x++;
    }

    charIterator; //Skip empty character and move to color specifier

    // parse active player (player's turn)
    if(fenString[charIterator] == 'w')
    {
        position->activePlayerColor = WHITE;
    }
    else
    {
        position->activePlayerColor = BLACK;
    }

    charIterator += 2; // Skip empty char and move to castling rights specifier

    // Parse castling rights
    if(fenString[46] != '-')
    {
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

        if(fenSubString.find('k') != std::string::npos)
        {
            charIterator++;
            position->blackCastlingRights = static_cast<CastlingRights>(position->blackCastlingRights | KINGSIDE);
        }

        if(fenSubString.find('q') != std::string::npos)
        {
            charIterator++;
            position->blackCastlingRights = static_cast<CastlingRights>(position->blackCastlingRights | QUEENSIDE);
        }
    }
    else
        charIterator++;

    charIterator++;

    // Parse en passant square
    if(fenString[charIterator] != '-')
    {
        position->enPassantSquareX = LetterToFile(fenString[charIterator]);
        position->enPassantSquareY = IntToRank(fenString[charIterator + 1]);
    }

    charIterator += 2;

    //parse fifty move counter
    position->fiftyMoveRuleCounter = std::stoi(&fenString[charIterator]);
    position->zobristKey = GeneratePositionHashKey(position);

    return position;
}
