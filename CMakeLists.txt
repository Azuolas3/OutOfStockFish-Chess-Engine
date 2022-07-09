cmake_minimum_required(VERSION 3.22)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess_engine main.cpp ChessBoard.cpp ChessBoard.h FenParser.cpp FenParser.h pieces.h MoveGenerator.cpp MoveGenerator.h bitboards.h Position.cpp Position.h BoardUtility.cpp BoardUtility.h)
