cmake_minimum_required(VERSION 3.22)
project(OutOfStockFish)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Utilities/AlgebraicNotationUtility.h
        Utilities/BoardUtility.h
        BoardRepresentation/ChessBoard.h
        AI/Evaluator.h
        Miscellaneous/FenParser.h
        MoveGenerator/Move.h
        MoveGenerator/MoveGenerator.h
        Utilities/PerftUtility.h
        BoardRepresentation/PieceList.h
        BoardRepresentation/pieces.h
        AI/PieceSquareTables.h
        BoardRepresentation/Position.h
        MoveGenerator/PseudoLegalMoveGenerator.h
        AI/Searcher.h
        Utilities/TimerUtility.h
        AI/TranspositionTable.h
        Miscellaneous/u64.h
        Utilities/ZobristUtility.h
        uci.h
        Utilities/InputReadUtility.h)

set(SOURCE_FILES
        Utilities/AlgebraicNotationUtility.cpp
        Utilities/BoardUtility.cpp
        BoardRepresentation/ChessBoard.cpp
        AI/Evaluator.cpp
        Miscellaneous/FenParser.cpp
        MoveGenerator/Move.cpp
        MoveGenerator/MoveGenerator.cpp
        Utilities/PerftUtility.cpp
        BoardRepresentation/PieceList.cpp
        BoardRepresentation/Position.cpp
        MoveGenerator/PseudoLegalMoveGenerator.cpp
        AI/Searcher.cpp
        Utilities/TimerUtility.cpp
        AI/TranspositionTable.cpp
        Utilities/ZobristUtility.cpp
        uci.cpp
        Utilities/InputReadUtility.cpp)

add_library(OutOfStockFish_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})