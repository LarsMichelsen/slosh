#pragma once

#include <stdint.h>

#include "Renderer.h"
#include "utils.h"

class Game;
class Player;
class Enemy;
class Exit;

class Entity {
private:
    uint16_t _position = 0;
    bool _spawned = false;

protected:
    Game *_game;

public:
    Entity(Game *game);
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
    void move_to(uint16_t pos);

    virtual void touches(Player *player){};
    virtual void touches(Enemy *enemy){};
    virtual void touches(Exit *exit){};
};
