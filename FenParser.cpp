//
// Created by Azuolas on 7/5/2022.
//

#include "FenParser.h"

using namespace ChessEngine;

ChessBoard FenParser::loadFen(std::string fenString)
{
    ChessBoard board;

    int charIterator = 0;
    for(int row = 7; row >= 0; row--)
    {
        for(int col = 0; col <= 8;)
        {
            char currChar = fenString[charIterator];
            //std::cout << col << " " << row << " " << charIterator << " " << currChar << " ";

            if(std::isdigit(currChar))
            {
                col += currChar - 48;
                charIterator++;
                continue;
            }

            if(currChar == '/')
            {
                charIterator++;
                break;
            }


            ChessEngine::PieceType pieceType = pieceTypeMap[tolower(currChar)];
            ChessEngine::PieceColor pieceColor;

            if(std::islower(currChar))
                pieceColor = ChessEngine::BLACK;
            else
                pieceColor = ChessEngine::WHITE;

            //std::cout << (pieceColor | pieceType) << std::endl;
            ChessEngine::Piece piece = static_cast<ChessEngine::Piece>(pieceColor | pieceType);
            board.pieces[col][row] = piece;

            charIterator++;
            col++;
        }
    }

    return board;
}
