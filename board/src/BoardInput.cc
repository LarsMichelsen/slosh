#include "BoardInput.h"

#include <Arduino.h>

BoardInput::BoardInput(const int pin_up, const int pin_down,
                       const int pin_attack_0, const int pin_attack_1,
                       const int pin_skip_level)
    : _pin_up(pin_up),
      _pin_down(pin_down),
      _pin_attack_0(pin_attack_0),
      _pin_attack_1(pin_attack_1),
      _pin_skip_level(pin_skip_level) {
    pinMode(_pin_up, INPUT_PULLUP);
    pinMode(_pin_down, INPUT_PULLUP);
    pinMode(_pin_attack_0, INPUT_PULLUP);
    pinMode(_pin_attack_1, INPUT_PULLUP);
    pinMode(_pin_skip_level, INPUT_PULLUP);
}

void BoardInput::handle_input(GameStateLevel *level, Player *player,
                              ms tick_time) {
    int state_up = digitalRead(_pin_up);
    int state_down = digitalRead(_pin_down);
    int state_attack_0 = digitalRead(_pin_attack_0);
    int state_attack_1 = digitalRead(_pin_attack_1);
    int state_skip_level = digitalRead(_pin_skip_level);

    if (state_skip_level == LOW) {
        level->mark_skipped();
        return;
    }

    if (state_up == LOW) {
        player->move(1, tick_time);
    } else if (state_down == LOW) {
        player->move(-1, tick_time);
    } else {
        player->move(0, tick_time);
    }

    player->attack(state_attack_0 == LOW or state_attack_1 == LOW, tick_time);
}
