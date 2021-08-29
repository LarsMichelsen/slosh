#pragma once
#include "GameState.h"
#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class GameStateWon final : public GameState {
private:
    bool _finished;
    ms _start_time;
    ms _phase_start_time;
    uint8_t _phase;

    uint8_t _show_phase0_last_index;
    int16_t _ship_pos;
    uint8_t _show_phase2_last_index;

    void set_phase(uint8_t phase, ms tick_time);
    void show_phase0(ms tick_time, ms duration);
    void show_phase1(ms tick_time, ms duration);
    void show_phase2(ms tick_time, ms duration);
    void show_phase3(ms tick_time, ms duration);
    void show_phase4(ms tick_time, ms duration);

public:
    GameStateWon(Renderer *renderer, Input *input, Sound *sound, Game *game);
    ~GameStateWon();

    virtual void enter() override;
    virtual void tick(ms tick_time) override;
    virtual void exit() override;
    virtual void next_state() override;
};
