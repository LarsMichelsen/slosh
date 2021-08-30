#pragma once

#include "../../common/GameStateLevel.h"
#include "../../common/Input.h"
#include "../../common/Player.h"

class BoardInput final : public Input {
private:
    int _pin_up, _pin_down, _pin_attack_0, _pin_attack_1, _pin_skip_level;

public:
    BoardInput(const int pin_up, const int pin_down, const int pin_attack_0,
               const int pin_attack_1, const int pin_skip_level);
    virtual void handle_input(GameStateLevel *level, Player *player,
                              ms tick_time) override;
};
