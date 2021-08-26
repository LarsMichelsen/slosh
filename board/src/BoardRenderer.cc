#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(const int brightness) {
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(_board_leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

BoardRenderer::~BoardRenderer() {}

void BoardRenderer::clear() { FastLED.clear(); }
void BoardRenderer::show() {
    clear();
    for (uint16_t i = 0; i < NUM_LEDS; i++)
        if (_leds[i].r != 0 || _leds[i].g != 0 || _leds[i].b != 0)
            _board_leds[i].setRGB(_leds[i].r, _leds[i].g, _leds[i].b);
    FastLED.show();
}
