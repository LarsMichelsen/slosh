#pragma once

#include "../common/Input.h"
#include "../common/Player.h"
#include "SDL.h"

class SDLInput final : public Input {
public:
    virtual void handle_input(Player *player) override;
};
