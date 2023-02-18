#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "pieces.h"
#include "Move.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"
#include "AlgebraicNotationUtility.h"
#include "Evaluator.h"
#include "Searcher.h"
#include "ZobristUtility.h"
#include "TranspositionTable.h"
#include "uci.h"
#include "PerftUtility.h"

using namespace ChessEngine;
using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;

int main() {
    InitializeZobrist();
    cout << "id name OutOfStockFish\n";
    cout << "id author Azuolas\n";
    cout << "uciok\n";
    UciLoop();

    return 0;
}


