#include <iostream>
#include "Utilities/ZobristUtility.h"
#include "uci.h"

using std::cout;

int main() {
    ChessEngine::InitializeZobrist();
//    cout << "id name OutOfStockFish\n";
//    cout << "id author Azuolas\n";
//    cout << "uciok\n";
    ChessEngine::UciLoop();

    return 0;
}


