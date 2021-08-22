#pragma once

#include <stdint.h>

#include "Renderer.h"
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
    void despawn() { _spawned = false; }
    bool is_spawned() { return _spawned; };
    void set_position(uint16_t pos) {
        if (pos > WORLD_MAX)
            _position = WORLD_MAX;
        else
            _position = pos;
    };
    uint16_t get_position() { return _position; };

    virtual void tick() = 0;
    virtual void show(Renderer *renderer) = 0;
    virtual void die() = 0;
};
