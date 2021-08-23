#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class Game;

class Exit : public Entity {
public:
    Exit(Game *game);
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
};
