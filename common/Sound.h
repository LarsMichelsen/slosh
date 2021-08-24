#pragma once

#include "utils.h"

// Abstract base for the sound
class Sound {
protected:
    virtual void play_note(uint16_t freq, uint8_t duration) = 0;

public:
    void play_test();
    void play_attack(ms duration, ms passed);
    void play_enemy_died();
};
