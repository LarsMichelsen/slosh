#include <FastLED.h>

#include "../../common/Renderer.h"
#include "utils.h"

#define CHIPSET WS2812B
#define LED_PIN 6
#define COLOR_ORDER GRB

class BoardRenderer final : public Renderer {
private:
    CRGB _board_leds[NUM_LEDS];

public:
    BoardRenderer(const int brightness);
    ~BoardRenderer();
    virtual void clear() override;
    virtual void show() override;
};
