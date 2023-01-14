//
// Created by Azuolas on 7/11/2022.
//

#include "AlgebraicNotationUtility.h"


int letterToFile(char letter) { return letterToFileMap[letter];}
int intToRank(int num) { return num-'0'-1;}

std::string MoveToString(Move move)
{
    std::string resultString;

    char startFile = IntToFile(move.startingX);
    char startRank = move.startingY + '0' + 1;

    char endFile = IntToFile(move.destinationX);
    char endRank = move.destinationY + '0' + 1;

    resultString.push_back(startFile);
    resultString.push_back(startRank);
    resultString.push_back(endFile);
    resultString.push_back(endRank);

    return resultString;
}

char IntToFile(int integer)
{
    return integer + 'a';
}

