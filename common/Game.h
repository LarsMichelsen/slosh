#pragma once

#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include "Renderer.h"

// Central entry point for the game
class Game {
private:
    Renderer *_renderer;
    Input *_input;
    Player _player;
    // Preinitialized objects - Not all are relevant during each level. It
    // depends on the logic of the level to make use of the objects.
    Enemy _enemies[5];

public:
    Game(Renderer *renderer, Input *input);
    void tick();
};
