#include "Game.h"

#include "GameState.h"
#include "Input.h"
#include "Player.h"

Game::Game(Renderer *renderer, Input *input, Sound *sound)
    : _state_level(new GameStateLevel(renderer, input, sound, this)),
      _state_init(new GameStateInit(renderer, input, sound, this)),
      _state_dead(new GameStateDead(renderer, input, sound, this)),
      _state_finished(new GameStateFinished(renderer, input, sound, this)) {
    _current_state = _state_init;
}

void Game::tick() {
    _current_state->tick();
    _current_state->next_state();
}

void Game::set_state(GameState *state) {
    _current_state->exit();
    _current_state = state;
    _current_state->enter();
}
