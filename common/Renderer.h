#pragma once

#include <stdint.h>

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
        virtual void clear() = 0;
        virtual void show() = 0;
};
