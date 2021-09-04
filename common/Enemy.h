#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class GameStateLevel;
class Player;

enum Movement {
    None,
    Up,
    Down,
    UpAndDown,
};

class Enemy : public Entity {
private:
    Movement _movement = Movement::None;
    ms _move_delay = 60;
    uint8_t _speed = 1;
    ms _next_move;
    pos_t _spawn_position;

    // Movement::BackAndForth specific
    bool _moving_down;
    uint8_t _range;

    // May follow the Player once in range
    uint8_t _follow_range;
    ms _follow_since;

    void init_movement(Movement movement);
    void follow_player(ms tick_time);

public:
    Enemy(GameStateLevel *level);
    virtual void tick(ms tick_time) override;
    virtual void show(Renderer *renderer, ms tick_time) override;
    virtual void die() override;
    void move(ms tick_time);

    void spawn(pos_t pos, Movement movement = Movement::None,
               ms move_delay = 60, uint8_t speed = 1, uint8_t follow_range = 0);

    void touches(Player *player) override;
};
