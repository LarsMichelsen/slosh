#pragma once

#include "Input.h"
#include "Player.h"
#include "Renderer.h"

// Central entry point for the game
class Game {
private:
    Renderer *_renderer;
    Input *_input;
    Player *_player;

public:
    Game(Renderer *renderer, Input *input);
    ~Game();
    void tick();
};
