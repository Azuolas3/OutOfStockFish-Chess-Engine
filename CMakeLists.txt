cmake_minimum_required(VERSION 3.22)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_subdirectory(src)

add_executable(chess_engine src/main.cpp)
target_link_libraries(chess_engine -static)
target_link_libraries(chess_engine chess_engine_lib)
add_subdirectory(tests)