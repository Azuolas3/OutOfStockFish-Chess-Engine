//
// Created by Azuolas on 7/5/2022.
//

#include "ChessBoard.h"

using namespace ChessEngine;

void ChessBoard::printBoard()
{
    wchar_t test = L'\u2659';

    std::map<int, wchar_t> symbolDictionary =
    {
            {0, L'\u26DA'},
            {2, L'\u2659'},
            {3, L'\u265F'},
            {4, L'\u2657'},
            {5, L'\u265D'},
            {6, L'\u2658'},
            {7, L'\u265E'},
            {8, L'\u2656'},
            {9, L'\u265C'},
            {10, L'\u2655'},
            {11, L'\u265B'},
            {12, L'\u2654'},
            {13, L'\u265A'}
    };

    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD written = 0;
            // explicitly call the wide version (which always accepts UTF-16)
            WriteConsoleW(handle, &(symbolDictionary[pieces[j][i]]), 1, &written, NULL);
        }
        std::cout << std::endl;
    }
}
