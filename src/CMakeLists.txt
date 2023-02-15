cmake_minimum_required(VERSION 3.22)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        AlgebraicNotationUtility.h
        BoardUtility.h
        ChessBoard.h
        Evaluator.h
        FenParser.h
        Move.h
        MoveGenerator.h
        PerftUtility.h
        PieceList.h
        pieces.h
        PieceSquareTables.h
        Position.h
        PseudoLegalMoveGenerator.h
        Searcher.h
        Timer.h
        TranspositionTable.h
        u64.h
        VectorUtility.h
        ZobristUtility.h
        )

set(SOURCE_FILES
        AlgebraicNotationUtility.cpp
        BoardUtility.cpp
        ChessBoard.cpp
        Evaluator.cpp
        FenParser.cpp
        Move.cpp
        MoveGenerator.cpp
        PerftUtility.cpp
        PieceList.cpp
        Position.cpp
        PseudoLegalMoveGenerator.cpp
        Searcher.cpp
        Timer.cpp
        TranspositionTable.cpp
        VectorUtility.cpp
        ZobristUtility.cpp
        )

add_library(chess_engine_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})