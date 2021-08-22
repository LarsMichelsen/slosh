#include "utils.h"

#include <math.h>

double map_to(double x, double in_min, double in_max, double out_min,
              double out_max) {
    return out_min + ((out_max - out_min) * (x - in_min)) / (in_max - in_min);
}

uint16_t pos_to_led(uint16_t pos) {
    uint16_t led = double(map_to((double)pos, (double)WORLD_MIN,
                                 (double)WORLD_MAX, 0.0, (double)NUM_LEDS - 1));
    if (led > NUM_LEDS - 1) return NUM_LEDS - 1;
    return led;
}
