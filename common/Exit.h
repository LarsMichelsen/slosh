#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class GameStateLevel;

class Exit : public Entity {
public:
    Exit(GameStateLevel *level);
    virtual void tick(ms tick_time) override;
    virtual void show(Renderer *renderer, ms tick_time) override;
    virtual void die() override;
};
