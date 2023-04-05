# OutOfStockFish-Chess-Engine
UCI-compatible chess engine project written in C++ 17

# Description
OutOfStockFish is a relatively simple chess engine, which is around ~1600 elo playing strength. It does not have a GUI of it's own, meaning you require a UCI-compatible
program (e.g. Arena, XBoard) to play or use comfortably.

The engine uses a simple 8x8 array and piece lists for board representation, piece square tables and material count for evaluation, as well as a minimax algorithm
with alpha-beta pruning, move ordering and a transposition table for search. There's also quiescence search and iterative deepening implemented as well.

# How to play against it
- Download any UCI-compatible chess GUI and load it there.
- Play it online! http://sodrapensijos.eu.pythonanywhere.com/

# Usage
The engine is designed to be loaded inside a UCI-compatible GUI, however you're still able to use it from console.
The following are commands the engine can parse:
- position [startpos | fen <fenstring>] moves <following moves from the given position> (provide a position to the engine, either the starting one or a different one through fen
- go [depth <specified depth> | wtime <ms> | btime <ms> | infinite] (start calculating on the current position set up with the "position" command)

More information on the UCI protocol: https://www.wbec-ridderkerk.nl/html/UCIProtocol.html
However, please keep in mind that this engine only implements the bare minimum necessary for playing.

# Noteworthy Files

Noteworthy files:
- src, subdirectory containing all the source code
- tests, subdirectory containing all the tests and the necessary files for the testing framework itself.
- AI, subdirectory containing all the code for position evaluation and searching.
- MoveGenerator, subdirectory containing all the code for move generation.
- Utilities, subdirectory containing various small functions used throughout the code, for example Perft benchmarking, Timers, Zobrist hashing, etc.
- BoardRepresentation, subdirectory containing all the code necessary for representing the position of the game.
- Miscellaneous, subdirectory containing everything that didn't find it's place elsewhere - Fen parser, small files for type defs, etc.
- CMakeLists.txt, file used to build the project with CMake.

# Build
To build you will need to do the following:
1. Make sure you have CMake and a C++ compiler installed.
2. in root directory ```cmake . ```
3. ```make OutOfStockFish ```

# Contributions
Feel free to contribute if you feel like it!
Currently the evaluation function is the weakest link, so feel free to add evaluation features such as:
- King safety
- Pawn structure

# Credits
Huge thanks to https://www.chessprogramming.org/ for a lot of great information on how to make chess engines and Sebastian Lague inspiring this project (https://youtu.be/U4ogK0MIzqk)
