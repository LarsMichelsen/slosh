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
    _start_time = get_ms();
    _finished = false;
}
void GameStateInit::exit() {}

void GameStateInit::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateInit::tick() {
    _renderer->tick();

    // First 3 flashes of the last LED
    for (uint8_t i = 0; i < 3; i++) {
        _renderer->set_led(NUM_LEDS - 1, 255, 64, 0);
        _renderer->show();
        sleep_for(50);
        _renderer->set_led(NUM_LEDS - 1, 0, 0, 0);
        _renderer->show();
        sleep_for(100);
    }

    // Move the players spaceship down to the spawn
    for (int16_t i = NUM_LEDS - 1; i > -40; i--) {
        // Create a flickering tail
        for (pos_t j = i >= 0 ? i : 0; j < i + 40; j++)
            if (random8(10) > 5) _renderer->fade_to_black(j, 64);
        _renderer->set_led(i + 40, 0, 0, 0);  // Ensure the tail max length
        _renderer->set_led(i - 1, 255, 200, 200);
        _renderer->set_led(i, 255, 64, 0);
        _renderer->show();
    }

    // Visualize the impact
    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t i = 0; i < 16; i += i + 1 * 2)
            if (random8(10) > 2) _renderer->set_led(i, 255, 64, 0);
        _renderer->show();
        sleep_for(50);
        for (uint8_t i = 0; i < 16; i += i + 1 * 2)
            _renderer->set_led(i, 0, 0, 0);
        _renderer->show();
        sleep_for(100);
    }

    sleep_for(10);

    _finished = true;
}
