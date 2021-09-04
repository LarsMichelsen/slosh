#pragma once

#include <math.h>

// Some defines to influence the game startup
#define INIT_STATE _state_init
#define INIT_LEVEL 0

// For get_ms()
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <time.h>
#endif

#include "stdint.h"

// The board currently makes ~50 fps max with the current
// LEDs. Apply this as cap to also make the emulator use
// a similar frame rate.
#define MS_PER_TICK 20

#define WORLD_MIN (uint16_t)0
#define WORLD_MAX (uint16_t)999

const int NUM_LEDS = 576;

typedef uint16_t pos_t;

uint16_t map_to(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min,
                uint16_t out_max);
uint16_t pos_to_led(pos_t pos);
pos_t distance(pos_t pos0, pos_t pos1);

typedef uint32_t ms;

ms get_ms();
void sleep_for(ms ms);

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

#ifndef ARDUINO
uint8_t random8();
uint8_t random8(uint8_t lim);
uint8_t random8(uint8_t min, uint8_t lim);
uint16_t random16();
uint16_t random16(uint16_t lim);
uint16_t random16(uint16_t min, uint16_t lim);
#endif
