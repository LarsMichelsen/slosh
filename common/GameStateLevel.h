#pragma once
#include "Enemy.h"
#include "Exit.h"
#include "GameState.h"
#include "Renderer.h"
#include "Sound.h"
#include "stdint.h"
#include "utils.h"

class Player;
class Input;

class GameStateLevel final : public GameState {
private:
    uint8_t _level;
    bool _mark_finished;  // Flag for the next tick to change the level
    ms _start_time = get_ms();

    void reload_level();
    uint8_t load_level(uint8_t level);

public:
    Player *_player;
    // Preinitialized objects - Not all are relevant during each level. It
    // depends on the logic of the level to make use of the objects.
    Enemy _enemies[5];
    Exit *_exit;

    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;
    virtual void next_state() override;
    GameStateLevel(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateLevel();

    ms time();
    bool is_complete();
    void mark_finished() { _mark_finished = true; };
    void despawn();
};
