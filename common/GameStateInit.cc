#include "GameStateInit.h"

#include "Game.h"
#include "Player.h"
#include "utils.h"

// Needed for utility functions like random8
#ifdef ARDUINO
#include "FastLED.h"
#endif

GameStateInit::GameStateInit(Renderer *renderer, Input *input, Sound *sound,
                             Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateInit::~GameStateInit() {}

void GameStateInit::enter() {
    _phase = 0;
    _start_time = _phase_start_time = get_ms();
    _ship_pos = NUM_LEDS - 1;
    _finished = false;
}
void GameStateInit::exit() {}

void GameStateInit::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateInit::tick(ms tick_time) {
    ms phase_duration = tick_time - _phase_start_time;

    // First 3 flashes of the last LED
    if (_phase == 0) {
        _sound->play_game_init_phase0(phase_duration);

        if ((phase_duration >= 0 && phase_duration < 50) ||
            (phase_duration >= 150 && phase_duration < 200) ||
            (phase_duration >= 300 && phase_duration < 350)) {
            _renderer->set_led(NUM_LEDS - 1, 255, 64, 0);
        } else {
            _renderer->set_led(NUM_LEDS - 1, 0, 0, 0);
        }
        if (phase_duration < 450) return;
        _phase = 1;
        _phase_start_time = tick_time;
        phase_duration = 0;
    }

    // Move the players spaceship down to the spawn
    if (_phase == 1) {
        _sound->play_game_init_phase1(phase_duration);

        // Create a flickering tail
        for (pos_t j = _ship_pos >= 0 ? _ship_pos : 0; j < _ship_pos + 40; j++)
            if (random8(10) > 5) _renderer->fade_to_black(j, 64);
        _renderer->set_led(_ship_pos + 40, 0, 0,
                           0);  // Ensure the tail max length
        _renderer->set_led(_ship_pos + 1, 255, 64, 0);
        _renderer->set_led(_ship_pos, 255, 200, 200);
        _ship_pos -= 1;
        if (_ship_pos >= -20) return;
        _phase = 2;
        _phase_start_time = tick_time;
        phase_duration = 0;
    }

    // Visualize the impact
    _phase = 2;
    if (_phase == 2) {
        _sound->play_game_init_phase2(phase_duration);

        for (uint8_t i = 0; i < 16; i++) {
            if (random8(10) > 5) _renderer->set_led(i, 255, 30, 0);
            if (random8(10) > 3) _renderer->set_led(i, 0, 0, 0);
        }
        if (phase_duration < 450) return;
        _phase = 3;
    }

    _finished = true;
}
