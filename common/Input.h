#pragma once

#include "Player.h"

// Abstract base for the input handling
class Input {
    public:
        virtual void handle_input(Player *player) = 0;
};

