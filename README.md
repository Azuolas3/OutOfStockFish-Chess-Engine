# OutOfStockFish-Chess-Engine
UCI-compatible chess engine project written in C++ 17

# Description
OutOfStockFish is a relatively simple chess engine, which is around ~1600 elo playing strength. It does not have a GUI of it's own, meaning you require a UCI-compatible
program (e.g. Arena, XBoard) to play or use comfortably.

The engine uses a simple 8x8 array and piece lists for board representation, piece square tables and material count for evaluation, as well as a minimax algorithm
with alpha-beta pruning, move ordering and a transposition table for search. There's also quiescence search and iterative deepening implemented as well.

# Usage
The engine is designed to be loaded inside a UCI-compatible GUI, however you're still able to use it from console.
The following are commands the engine can parse:
- position [startpos | fen <fenstring>] moves <following moves from the given position> (provide a position to the engine, either the starting one or a different one through fen
- go [depth <specified depth> | wtime <ms> | btime <ms> | infinite] (start calculating on the current position set up with the "position" command)

More information on the UCI protocol: https://www.wbec-ridderkerk.nl/html/UCIProtocol.html 

# Contributions
Feel free to contribute if you feel like it!
Currently the evaluation function is the weakest link, so feel free to add evaluation features such as:
- King safety
- Pawn structure

# Credits
Huge thanks to https://www.chessprogramming.org/ for a lot of great information on how to make chess engines and Sebastian Lague inspiring this project (https://youtu.be/U4ogK0MIzqk)
