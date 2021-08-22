#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"
#include "utils.h"

class Player : public Entity {
private:
    uint8_t _speed = 4;
    bool _attacking = false;

public:
    Player();
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;

    void move(int8_t direction);
    void attack(bool attacking);
};
