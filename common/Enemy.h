#pragma once

#include <limits>

#include "Entity.h"
#include "Renderer.h"
#include "stdint.h"

class Enemy : public Entity {
public:
    Enemy();
    virtual void tick() override;
    virtual void show(Renderer *renderer) override;
};
