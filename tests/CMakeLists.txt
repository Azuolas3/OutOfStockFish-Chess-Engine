cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

add_executable(Tests_run PieceTests.cpp PerftTests.cpp ZobristTests.cpp AlgebraicNotationUtilityTests.cpp)
target_link_libraries(Tests_run chess_engine_lib)
target_link_libraries(Tests_run -static)