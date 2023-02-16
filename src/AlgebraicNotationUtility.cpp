//
// Created by Azuolas on 7/11/2022.
//

#include "AlgebraicNotationUtility.h"


int letterToFile(char letter) { return letterToFileMap[letter];}
int intToRank(int num) { return num-'0'-1;}

std::string MoveToString(const Move& move)
{
    std::string resultString;
    MoveType moveType = move.moveType;

    char startFile = IntToFile(move.startingX);
    char startRank = move.startingY + '0' + 1;

    char endFile = IntToFile(move.destinationX);
    char endRank = move.destinationY + '0' + 1;

    resultString.push_back(startFile);
    resultString.push_back(startRank);
    resultString.push_back(endFile);
    resultString.push_back(endRank);

    if(IsPromotionType(moveType))
    {
        char promotionChar = GetCharFromPromotionType(moveType);
        resultString.push_back(promotionChar);
    }

    return resultString;
}

Move StringToMove(const std::string &moveString)
{
    int startingX = letterToFile(moveString[0]);
    int startingY = intToRank(moveString[1]);

    int destinationX = letterToFile(moveString[2]);
    int destinationY = intToRank(moveString[3]);

    MoveType moveType = QUIET;
    if(moveString.length() == 5)
    {
        moveType = GetMoveTypeFromChar(moveString[4]);
    }

    return Move(startingX, startingY, destinationX, destinationY);
}

char IntToFile(int integer)
{
    return integer + 'a';
}

