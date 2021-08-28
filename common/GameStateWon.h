#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateWon final : public GameState {
private:
    bool _finished;
    ms _start_time;

public:
    GameStateWon(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateWon();

    virtual void enter() override;
    virtual void tick(ms tick_time) override;
    virtual void exit() override;
    virtual void next_state() override;
};
