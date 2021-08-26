#pragma once

#include <stdint.h>

#include "utils.h"

struct LED {
    uint8_t r, g, b;

    inline LED& set_rgb(uint8_t nr, uint8_t ng, uint8_t nb) {
        r = nr;
        g = ng;
        b = nb;
        return *this;
    }
};

// Abstract base for the emulator and fastled renderers.
// It's task is to display the state of the game.
class Renderer {
public:
    LED _leds[NUM_LEDS] = {0, 0, 0};

    void tick() {
        // Clear the logical representation of the map
        for (pos_t i = 0; i < NUM_LEDS; i++) {
            _leds[i].r = 0;
            _leds[i].g = 0;
            _leds[i].b = 0;
        }
    };
    void set_led(pos_t pos, uint8_t r, uint8_t g, uint8_t b) {
        if (pos < WORLD_MIN or pos > WORLD_MAX) return;
        _leds[pos].set_rgb(r, g, b);
    };

    void fill_solid(pos_t pos, int num, const struct LED& color) {
        for (int i = 0; i < num; ++i) {
            if (pos < WORLD_MIN or pos > WORLD_MAX) continue;
            _leds[i] = color;
        }
    }

    void fade_to_black(pos_t pos, uint8_t value) {
        if (pos < WORLD_MIN or pos > WORLD_MAX) return;
        uint8_t r = _leds[pos].r, g = _leds[pos].g, b = _leds[pos].b;

        r = (r <= 10) ? 0 : (uint8_t)r - (r * value / 256);
        g = (g <= 10) ? 0 : (uint8_t)g - (g * value / 256);
        b = (b <= 10) ? 0 : (uint8_t)b - (b * value / 256);

        _leds[pos].set_rgb(r, g, b);
    }

    virtual void clear() = 0;
    virtual void show() = 0;
};
