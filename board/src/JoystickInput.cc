#include "JoystickInput.h"

#include <Arduino.h>

JoystickInput::JoystickInput(const int pin_up, const int pin_down,
                             const int pin_attack_0, const int pin_attack_1)
    : _pin_up(pin_up),
      _pin_down(pin_down),
      _pin_attack_0(pin_attack_0),
      _pin_attack_1(pin_attack_1) {
    pinMode(_pin_up, INPUT_PULLUP);
    pinMode(_pin_down, INPUT_PULLUP);
    pinMode(_pin_attack_0, INPUT_PULLUP);
    pinMode(_pin_attack_1, INPUT_PULLUP);
}

void JoystickInput::handle_input(Player *player) {
    int state_up = digitalRead(_pin_up);
    int state_down = digitalRead(_pin_down);
    int state_attack_0 = digitalRead(_pin_attack_0);
    int state_attack_1 = digitalRead(_pin_attack_1);

    if (state_up == LOW) {
        player->move(1);
    } else if (state_down == LOW) {
        player->move(-1);
    } else {
        player->move(0);
    }

    player->attack(state_attack_0 == LOW or state_attack_1 == LOW);
}
