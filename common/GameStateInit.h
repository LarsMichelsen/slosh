#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateInit final : public GameState {
private:
    bool _finished;
    ms _start_time;

public:
    GameStateInit(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateInit();

    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;
    virtual void next_state() override;
};
