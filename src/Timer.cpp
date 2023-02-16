//
// Created by Azuolas on 2/8/2023.
//

#include <iostream>
#include "Timer.h"

namespace ChessEngine {
    void StartTimer(int seconds, const std::function<void()> &func)
    {
        if(seconds <= 0) // don't do anything if the specified time is incorrect
            return;

        //std::cout << "started timer" << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        func();
        //std::cout << "timer done" << '\n';
    }
} // ChessEngine