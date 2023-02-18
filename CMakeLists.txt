cmake_minimum_required(VERSION 3.22)
project(OutOfStockFish)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_subdirectory(src)

add_executable(OutOfStockFish src/main.cpp)
target_link_libraries(OutOfStockFish -static)
target_link_libraries(OutOfStockFish OutOfStockFish_lib)
add_subdirectory(tests)