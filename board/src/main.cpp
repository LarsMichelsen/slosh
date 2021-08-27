#include <Arduino.h>
#include <FastLED.h>

#include "BoardRenderer.h"
#include "BoardSound.h"
#include "Game.h"
#include "JoystickInput.h"
#include "utils.h"

BoardRenderer renderer(128);
BoardSound sound;
JoystickInput input(2, 3, 4, 5);
Game game(&renderer, &input, &sound);

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
}

void loop() {
    EVERY_N_MILLISECONDS(MS_PER_TICK) {
        game.tick();
        renderer.show();
        // debug << "Current FPS: " << FastLED.getFPS() << "\n";
    }
}
