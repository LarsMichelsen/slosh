#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class Game;

class Enemy : public Entity {
private:
    Game *_game;

public:
    Enemy(Game *game);
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;
    virtual void die() override;
};
