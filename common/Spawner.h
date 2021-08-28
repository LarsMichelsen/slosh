#pragma once

#include "Enemy.h"
#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class GameStateLevel;

class Spawner : public Entity {
private:
    ms _spawn_interval = 5000;
    ms _next_spawn = 0;
    Movement _spawn_movement = Movement::None;

public:
    Spawner(GameStateLevel *level);
    virtual void tick(ms tick_time) override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
    void move();

    Spawner *spawn(pos_t pos, ms spawn_interval, Movement spawn_movement);
};
