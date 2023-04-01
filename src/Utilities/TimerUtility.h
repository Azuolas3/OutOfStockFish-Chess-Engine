//
// Created by Azuolas on 2/8/2023.
//

#ifndef CHESS_ENGINE_TIMERUTILITY_H
#define CHESS_ENGINE_TIMERUTILITY_H

#include <functional>
#include <future>
#include <chrono>
#include <thread>

namespace ChessEngine
{
    void StartTimer(int milliseconds, const std::function<void()> &func);
} // ChessEngine

#endif //CHESS_ENGINE_TIMERUTILITY_H
