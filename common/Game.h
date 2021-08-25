#pragma once

#include "GameState.h"
#include "GameStateDead.h"
#include "GameStateFinished.h"
#include "GameStateLevel.h"
#include "Renderer.h"
#include "Sound.h"
#include "utils.h"

class Input;

// Central entry point for the game. It implements a finite state machine
// switching between different states of the game. The major one is the
// GameStateLevel in which the gaming happens. The other states are mainly
// realizing transition phases where specific visualizations or similar things
// are done.
class Game {
public:
    GameState *_current_state;
    GameStateLevel *_state_level;
    GameStateDead *_state_dead;
    GameStateFinished *_state_finished;

    Game(Renderer *renderer, Input *input, Sound *sound);
    void tick();
    void set_state(GameState *state);
};
