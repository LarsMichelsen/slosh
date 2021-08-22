#pragma once

#include "../../common/Input.h"
#include "../../common/Player.h"

class JoystickInput final : public Input {
private:
    int _pin_up, _pin_down, _pin_attack_0, _pin_attack_1;

public:
    JoystickInput(const int pin_up, const int pin_down, const int pin_attack_0,
                  const int pin_attack_1);
    virtual void handle_input(Player *player) override;
};
