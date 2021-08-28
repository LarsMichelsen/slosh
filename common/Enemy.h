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
    ms _next_move;
    pos_t _spawn_position;

    // Movement::BackAndForth specific
    bool _moving_down;
    uint8_t _range;

    void init_movement(Movement movement);

public:
    Enemy(GameStateLevel *level);
    virtual void tick(ms tick_time) override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
    void move(ms tick_time);

    Enemy *spawn(pos_t pos);
    Enemy *moving(Movement movement, ms move_delay = 60);

    void touches(Player *player) override;
};
