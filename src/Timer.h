//
// Created by Azuolas on 2/8/2023.
//

#ifndef CHESS_ENGINE_TIMER_H
#define CHESS_ENGINE_TIMER_H

#include <functional>
#include <future>
#include <chrono>
#include <thread>

namespace ChessEngine
{
    void StartTimer(int seconds, const std::function<void()> &func);
} // ChessEngine

#endif //CHESS_ENGINE_TIMER_H
