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
    const static uint8_t _move_delay = 60;
    uint16_t _next_move;
    pos_t _spawn_position;

    // Movement::BackAndForth specific
    bool _moving_down;
    uint8_t _range;

    void init_movement(Movement movement);

public:
    Enemy(GameStateLevel *level);
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
    void spawn(pos_t pos, Movement movement);
    void move();

    void touches(Player *player) override;
};
