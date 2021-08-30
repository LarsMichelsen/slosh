#pragma once

#include "../common/GameStateLevel.h"
#include "../common/Input.h"
#include "../common/Player.h"
#include "SDL.h"

class SDLInput final : public Input {
public:
    virtual void handle_input(GameStateLevel *level, Player *player,
                              ms tick_time) override;
};
