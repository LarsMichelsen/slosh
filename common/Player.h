#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class Player : public Entity {
public:
    Player();
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;

    void move(int8_t direction);
    void attack();
};
