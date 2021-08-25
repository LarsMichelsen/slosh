#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class GameStateLevel;

class Exit : public Entity {
public:
    Exit(GameStateLevel *level);
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
};
