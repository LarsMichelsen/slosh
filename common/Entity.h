#pragma once

#include <stdint.h>

#include <algorithm>

#include "Renderer.h"
#include "iostream"
#include "utils.h"

class Entity {
private:
    uint16_t _position = 0;
    bool _spawned = false;

public:
    void spawn(uint16_t pos) {
        set_position(pos);
        _spawned = true;
    };
    bool is_spawned() { return _spawned; };
    void set_position(uint16_t pos) {
        _position = clamp(pos, WORLD_MIN, WORLD_MAX);
    };
    uint16_t get_position() { return _position; };

    virtual void tick() = 0;
    virtual void show(Renderer *renderer) = 0;
};
