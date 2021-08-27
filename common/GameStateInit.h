#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateInit final : public GameState {
private:
    bool _finished;
    ms _start_time;
    ms _phase_start_time;
    uint8_t _phase;
    int16_t _ship_pos;

public:
    GameStateInit(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateInit();

    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;
    virtual void next_state() override;
};
