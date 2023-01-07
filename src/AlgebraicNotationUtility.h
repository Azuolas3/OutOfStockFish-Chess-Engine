//
// Created by Azuolas on 7/10/2022.
//

#ifndef CHESS_ENGINE_ALGEBRAICNOTATIONUTILITY_H
#define CHESS_ENGINE_ALGEBRAICNOTATIONUTILITY_H

#include <map>

inline std::map<char, int> letterToFileMap =
{
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7},
};

int letterToFile(char letter);
int intToRank(int num);



#endif //CHESS_ENGINE_ALGEBRAICNOTATIONUTILITY_H
