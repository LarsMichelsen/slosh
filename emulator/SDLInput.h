#pragma once

#include "SDL.h"
#include "../common/Input.h"
#include "../common/Player.h"

class SDLInput final : public Input {
public:
    virtual void handle_input(Player *player) override;
};

