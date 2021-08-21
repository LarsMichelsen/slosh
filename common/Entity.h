#pragma once

#include <stdint.h>

#include <algorithm>

#include "Renderer.h"
#include "iostream"
#include "utils.h"

class Entity {
private:
    uint16_t _position = 0;

public:
    void set_position(uint16_t pos) {
        _position = clamp(pos, WORLD_MIN, WORLD_MAX);
        std::cout << "orig: " << pos << "clamped " << _position << "\n";
    };
    uint16_t get_position() { return _position; };

    virtual void tick() = 0;
    virtual void show(Renderer *renderer) = 0;
};
