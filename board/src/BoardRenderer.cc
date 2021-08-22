#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(const int brightness) {
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(_board_leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

BoardRenderer::~BoardRenderer() {}

void BoardRenderer::clear() { FastLED.clear(); }
void BoardRenderer::show() {
    clear();
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        _board_leds[i].r = _leds[i].r;
        _board_leds[i].g = _leds[i].g;
        _board_leds[i].b = _leds[i].b;
    }
    FastLED.show();
}
