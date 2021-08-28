#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateDead final : public GameState {
private:
    bool _finished;
    ms _start_time;

public:
    GameStateDead(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateDead();

    virtual void enter() override;
    virtual void tick(ms tick_time) override;
    virtual void exit() override;
    virtual void next_state() override;
};
