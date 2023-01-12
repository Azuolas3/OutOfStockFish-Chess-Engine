//
// Created by Azuolas on 1/12/2023.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <functional>

struct Move
{
    Move()
    = default;

    Move(int fromX, int fromY, int toX, int toY)
    {
        startingX = fromX;
        startingY = fromY;
        destinationX = toX;
        destinationY = toY;
    }

    int startingX, startingY;
    int destinationX, destinationY;
    std::function<void()> additionalAction = nullptr;
};

#endif //CHESS_ENGINE_MOVE_H
