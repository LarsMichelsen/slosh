#pragma once

#include "Enemy.h"
#include "Exit.h"
#include "Renderer.h"
#include "utils.h"

class Player;
class Input;

// Central entry point for the game
class Game {
private:
    Renderer *_renderer;
    Input *_input;

    ms _start_time = get_ms();
    uint8_t _level;

public:
    Player *_player;
    // Preinitialized objects - Not all are relevant during each level. It
    // depends on the logic of the level to make use of the objects.
    Enemy _enemies[5];
    Exit *_exit;

    Game(Renderer *renderer, Input *input);
    void tick();
    ms time();
    uint8_t load_level(uint8_t level);
    bool is_level_complete();
    void despawn_level();
    void finish_level();
    void reload_level();
};
