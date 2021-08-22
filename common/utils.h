#pragma once

#include <math.h>

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

uint16_t map_to(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min,
                uint16_t out_max);
uint16_t pos_to_led(uint16_t pos);

typedef uint32_t ms;

ms get_ms();
