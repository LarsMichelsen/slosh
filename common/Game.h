#pragma once

#include "Renderer.h"

// Central entry point for the game
class Game {
    private:
        Renderer *_renderer;
    public:
        Game(Renderer *renderer);
        void tick();
};
