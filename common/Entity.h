#pragma once

#include <stdint.h>

#include "Renderer.h"
#include "utils.h"

class GameStateLevel;
class Player;
class Enemy;
class Spawner;
class Exit;

class Entity {
private:
    pos_t _position = 0;
    bool _spawned = false;

protected:
    GameStateLevel *_level;

public:
    Entity(GameStateLevel *level);
    void spawn(pos_t pos) {
        set_position(pos);
        _spawned = true;
    };
    void despawn() { _spawned = false; }
    bool is_spawned() { return _spawned; };
    void set_position(pos_t pos) {
        if (pos > WORLD_MAX)
            _position = WORLD_MAX;
        else
            _position = pos;
    };
    pos_t get_position() { return _position; };

    virtual void tick(ms tick_time) = 0;
    virtual void show(Renderer *rendere, ms tick_timer) = 0;
    virtual void die() = 0;
    void move_to(pos_t pos);

    virtual void touches(Player *player){};
    virtual void touches(Enemy *enemy){};
    virtual void touches(Spawner *spawner){};
    virtual void touches(Exit *exit){};
};
