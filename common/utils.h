#pragma once

#include <math.h>

// For get_ms()
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <time.h>
#endif

#include "stdint.h"

#define MS_PER_TICK 16  // ~ 63 fps

#define WORLD_MIN (uint16_t)0
#define WORLD_MAX (uint16_t)999

const int NUM_LEDS = 576;

typedef uint16_t pos_t;

uint16_t map_to(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min,
                uint16_t out_max);
uint16_t pos_to_led(pos_t pos);

typedef uint32_t ms;

ms get_ms();

// Allow platform independent debug logging. It uses serial output of the
// board and stdout of the emulator.
// Use it like this: `debug << "bla" << 1 << "\n";`
#ifdef ARDUINO
#define debug Serial
template <class T>
inline Print &operator<<(Print &obj, T arg) {
    obj.print(arg);
    return obj;
}
#else
#include <iostream>
#define debug std::cout
#endif
