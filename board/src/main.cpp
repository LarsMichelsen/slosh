#include <Arduino.h>
#include <FastLED.h>

#include "BoardInput.h"
#include "BoardRenderer.h"
#include "BoardSound.h"
#include "Game.h"
#include "utils.h"

BoardRenderer renderer(128);
BoardSound sound;
BoardInput input(2, 3, 4, 5, 7);
Game game(&renderer, &input, &sound);

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
}

void loop() {
    EVERY_N_MILLISECONDS(MS_PER_TICK) {
        game.tick(get_ms());
        renderer.show();
        // debug << "Current FPS: " << FastLED.getFPS() << "\n";
    }
}
