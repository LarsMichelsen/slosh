#pragma once

#include <stdint.h>

#include <algorithm>

const int NUM_LEDS = 576;

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// Abstract base for the emulator and fastled renderers.
// It's task is to display the state of the game.
class Renderer {
public:
    RGB _leds[NUM_LEDS] = {0, 0, 0};

    void tick() {
        // Clear the map
        for (uint16_t i = 0; i < NUM_LEDS; i++) {
            _leds[i].r = 0;
            _leds[i].g = 0;
            _leds[i].b = 0;
        }
    };
    virtual void clear() = 0;
    virtual void show() = 0;
};
