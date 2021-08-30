#pragma once
#include "Enemy.h"
#include "Exit.h"
#include "GameState.h"
#include "Renderer.h"
#include "Sound.h"
#include "Spawner.h"
#include "stdint.h"
#include "utils.h"

class Player;
class Input;

class GameStateLevel final : public GameState {
private:
    uint8_t _level;
    bool _mark_finished;  // Flag for the next tick to change the level
    bool _mark_won;       // Flag for the next tick to play game won effect
    bool _mark_skipped;   // Flag for the next tick to load the next level
    ms _start_time = get_ms();

    void reload_level();
    void load_next_level();
    uint8_t load_level(uint8_t level);

public:
    Player *_player;
    // Preinitialized objects - Not all are relevant during each level. It
    // depends on the logic of the level to make use of the objects.
    Enemy _enemies[7];
    Spawner _spawners[1];
    Exit *_exit;

    virtual void enter() override;
    virtual void tick(ms tick_time) override;
    virtual void exit() override;
    virtual void next_state() override;
    GameStateLevel(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateLevel();

    bool is_complete();
    Enemy *get_unspawned_enemy();
    void mark_finished() {
        _mark_finished = true;
        if (_level == 8) _mark_won = true;
    };
    void mark_skipped() { _mark_skipped = true; };
    void despawn();
};
