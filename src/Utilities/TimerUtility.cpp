//
// Created by Azuolas on 2/8/2023.
//

#include "TimerUtility.h"

namespace ChessEngine
{
    void StartTimer(int milliseconds, const std::function<void()> &func)
    {
        if(milliseconds <= 0) // don't do anything if the specified time is incorrect
            return;

        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        func();
    }
} // ChessEngine