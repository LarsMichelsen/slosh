#pragma once

#include <limits>
#include "stdint.h"

#include "Entity.h"
#include "Renderer.h"

class Player: public Entity {
    public:
        Player();
        virtual void tick() override;
        virtual void show(Renderer *renderer) override;
        
        void spawn();
        void move(int8_t direction);
        void attack();
};
