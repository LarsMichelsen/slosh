#include "GameStateWon.h"

#ifdef ARDUINO
#include "FastLED.h"
#endif

#include "Game.h"
#include "Player.h"
#include "utils.h"

GameStateWon::GameStateWon(Renderer *renderer, Input *input, Sound *sound,
                           Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateWon::~GameStateWon() {}

void GameStateWon::enter() {
    _start_time = _phase_start_time = get_ms();
    _phase = 0;
    _finished = false;

    _show_phase0_last_index = 255;
    _ship_pos = 0;
}
void GameStateWon::exit() {}

void GameStateWon::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateWon::tick(ms tick_time) {
    ms phase_duration = tick_time - _phase_start_time;
    switch (_phase) {
        case 0:
            show_phase0(tick_time, phase_duration);
            return;
        case 1:
            show_phase1(tick_time, phase_duration);
            return;
        case 2:
            show_phase2(tick_time, phase_duration);
            return;
        case 3:
            show_phase3(tick_time, phase_duration);
            return;
        case 4:
            if (phase_duration > 1000) _finished = true;
            return;
    }
}

// Green waves
void GameStateWon::show_phase0(ms tick_time, ms duration) {
    uint8_t heights[] = {0,  4, 0,  10, 0, 8,  2, 0,  16, 0, 12, 0,  8, 0,  6,
                         0,  2, 0,  14, 0, 12, 0, 10, 0,  5, 0,  15, 0, 13, 0,
                         16, 0, 10, 0,  8, 0,  6, 0,  4,  0, 6,  0,  3, 0,  5,
                         0,  2, 0,  4,  0, 1,  0, 3,  0,  1, 0,  2,  0, 1};
    ms step_duration = 40;
    uint8_t num_steps = sizeof(heights) / sizeof(uint8_t);

    uint8_t index = duration / step_duration;
    if (index >= num_steps) {
        set_phase(1, tick_time);
        return;  // Finish this phase
    }

    if (index == _show_phase0_last_index) return;  // Do not execute one twice
    _show_phase0_last_index = index;

    for (uint8_t i = 0; i < 30; i++) {
        _renderer->_leds[i].set_rgb(0, 0, 0);
    }

    uint8_t height = heights[index];
    uint8_t dim_step = height > 0 ? 200 / height : 0;
    for (uint8_t i = 0; i < height; i++)
        _renderer->_leds[i].set_rgb(0, 255 - (i * dim_step), 0);
}

// Spaceship starting
void GameStateWon::show_phase1(ms tick_time, ms duration) {
    uint8_t speed = _ship_pos / 10 + 1;
    if (speed > 5) speed = 5;

    for (uint8_t i = 1; i <= speed; i++)  // Ensure the tail max length
        _renderer->set_led(_ship_pos - 40 - i, 0, 0, 0);
    for (uint8_t i = 1; i <= speed; i++)
        _renderer->set_led(_ship_pos - i, 255, 80, 0);
    for (int16_t i = _ship_pos - 40; i < _ship_pos; i++)
        if (random8(10) > 3) _renderer->fade_to_black(i, 100);
    _renderer->set_led(_ship_pos, 255, 200, 200);

    _ship_pos += speed;

    if (_ship_pos <= NUM_LEDS + 20) return;
    set_phase(2, tick_time);
}

// Spaceship gone
void GameStateWon::show_phase2(ms tick_time, ms duration) {
    uint8_t heights[] = {0, 1, 0, 2, 0, 20, 0, 1, 0, 2, 10, 0, 20, 0};
    ms step_duration = 40;
    uint8_t num_steps = sizeof(heights) / sizeof(uint8_t);

    uint8_t index = duration / step_duration;
    if (index >= num_steps) {
        set_phase(3, tick_time);
        return;  // Finish this phase
    }

    if (index == _show_phase2_last_index) return;  // Do not execute one twice
    _show_phase2_last_index = index;

    for (uint8_t i = 0; i < 30; i++) {
        _renderer->_leds[NUM_LEDS - 1 - i].set_rgb(0, 0, 0);
    }

    uint8_t height = heights[index];
    uint8_t dim_step = height > 0 ? 100 / height : 0;
    for (uint8_t i = 0; i < height; i++)
        _renderer->_leds[NUM_LEDS - 1 - i].set_rgb(255 - (i * dim_step),
                                                   153 - (i * dim_step), 0);
}

// Stars
void GameStateWon::show_phase3(ms tick_time, ms duration) {
    for (pos_t i = 0; i < NUM_LEDS; i++)
        if (random8(10) > 5) _renderer->fade_to_black(i, 64);

    if (duration > 10000) {
        set_phase(4, tick_time);
        return;  // Finish this phase
    }

    if (random8(10) > 3 && duration < 9300) {
        uint16_t led_num = random16(NUM_LEDS);
        _renderer->_leds[led_num].set_rgb(255, 255, 255);
    }
}

void GameStateWon::set_phase(uint8_t phase, ms tick_time) {
    _phase = phase;
    _phase_start_time = tick_time;
}
