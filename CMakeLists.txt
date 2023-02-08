cmake_minimum_required(VERSION 3.22)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess_engine src/main.cpp src/PieceList.cpp src/PieceList.h src/ChessBoard.cpp src/ChessBoard.h src/FenParser.cpp src/FenParser.h src/pieces.h src/PseudoLegalMoveGenerator.cpp src/PseudoLegalMoveGenerator.h src/bitboards.h src/Position.cpp src/Position.h src/BoardUtility.cpp src/BoardUtility.h src/AlgebraicNotationUtility.h src/AlgebraicNotationUtility.cpp src/LegalityTester.cpp src/LegalityTester.h src/MoveGenerator.cpp src/MoveGenerator.h src/VectorUtility.cpp src/VectorUtility.h src/PerftUtility.cpp src/PerftUtility.h src/Move.h src/Move.cpp src/Evaluator.cpp src/Evaluator.h src/Searcher.cpp src/Searcher.h src/PieceSquareTables.h src/ZobristUtility.cpp src/ZobristUtility.h src/u64.h src/TranspositionTable.cpp src/TranspositionTable.h src/Timer.cpp src/Timer.h)
target_link_libraries(chess_engine -static)