#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateFinished final : public GameState {
private:
    bool _finished;
    ms _start_time;

public:
    GameStateFinished(Renderer *renderer, Input *input, Sound *sound,
                      Game *game);
    ~GameStateFinished();

    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;
    virtual void next_state() override;
};
