#pragma once

#include <stdlib.h>

#include "Entity.h"
#include "Exit.h"
#include "Renderer.h"
#include "stdint.h"
#include "utils.h"

class GameStateLevel;
class Enemy;

struct Task {
    bool active;
    ms since;
};

class Player : public Entity {
private:
    uint8_t _speed = 4;
    bool _wants_to_attack = false;
    Task _attacking{.active = false, .since = 0};
    Task _moving{.active = false, .since = 0};

    static constexpr ms _attack_duration{100};
    static constexpr ms _attack_delay{50};
    static const uint8_t _attack_range = 4;

    void show_player(Renderer *renderer);
    void show_attack(Renderer *renderer, ms tick_time);

public:
    Player(GameStateLevel *level);
    virtual void tick(ms tick_time) override;
    virtual void show(Renderer *renderer, ms tick_time) override;

    void move(int8_t direction, ms tick_time);
    void attack(bool wants_to_attack, ms tick_time);
    bool is_attacking(Entity *entity);
    virtual void die() override;

    void touches(Enemy *enemy) override;
    void touches(Exit *exit) override;
};
