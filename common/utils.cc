#include "utils.h"

double map_to(double x, double in_min, double in_max, double out_min,
              double out_max) {
    return out_min + ((out_max - out_min) * (x - in_min)) / (in_max - in_min);
}

uint16_t pos_to_led(pos_t pos) {
    uint16_t led = double(map_to((double)pos, (double)WORLD_MIN,
                                 (double)WORLD_MAX, 0.0, (double)NUM_LEDS - 1));
    if (led > NUM_LEDS - 1) return NUM_LEDS - 1;
    return led;
}

uint32_t start_ms = 0;

// Return miliseconds since board init and on emulator since the first call to
// this function.
ms get_ms() {
#ifdef ARDUINO
    return millis();
#else
    struct timespec _t;

    if (start_ms == 0) {
        struct timespec _start_time;
        clock_gettime(CLOCK_MONOTONIC, &_start_time);
        start_ms =
            _start_time.tv_sec * 1000 + lround(_start_time.tv_nsec / 1.0e6);
    }

    clock_gettime(CLOCK_MONOTONIC, &_t);
    return (_t.tv_sec * 1000 + lround(_t.tv_nsec / 1.0e6)) - start_ms;
#endif
}

#ifndef ARDUINO
#include <unistd.h>
#endif
void sleep_for(ms ms) {
#ifdef ARDUINO
    delay(ms);
#else
    usleep(ms * 1000);
#endif
}

#ifndef ARDUINO
#include <cstdlib>
uint8_t random8() { return rand() % 256; }
uint8_t random8(uint8_t lim) {
    uint8_t r = random8();
    r = (r * lim) >> 8;
    return r;
}
uint8_t random8(uint8_t min, uint8_t lim) {
    uint8_t delta = lim - min;
    uint8_t r = random8(delta) + min;
    return r;
}
uint16_t random16() { return rand() % 65536; }
uint16_t random16(uint16_t lim) {
    uint16_t r = random16();
    uint32_t p = (uint32_t)lim * (uint32_t)r;
    r = p >> 16;
    return r;
}
uint16_t random16(uint16_t min, uint16_t lim) {
    uint16_t delta = lim - min;
    uint16_t r = random16(delta) + min;
    return r;
}
#endif
