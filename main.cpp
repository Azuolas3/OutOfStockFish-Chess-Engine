#include <iostream>
#include "pieces.h"
#include "windows.h"
#include "FenParser.h"

using namespace ChessEngine;

int main() {
    Piece test[8][8] = { EMPTY };
    //for(auto &test : test)
    //std::fill(&test[0][0], &test[7][7], EMPTY);
    int test2;
    FenParser fenParser;
    ChessBoard board = fenParser.loadFen(fenParser.startingFenString);
    std::cout << "HELLO WORLD BLET " << test[2][0] << std::endl;
    //WriteConsoleW(handle, L"\u265E ", 2, &written, NULL);
    //std::cout << board.pieces[0][0] << " " << board.pieces[1][7];


    board.printBoard();

    return 0;
}

