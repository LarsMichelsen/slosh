#include "Game.h"

#include "GameState.h"
#include "Input.h"
#include "Player.h"

Game::Game(Renderer *renderer, Input *input, Sound *sound)
    : _state_level(new GameStateLevel(renderer, input, sound, this)),
      _state_init(new GameStateInit(renderer, input, sound, this)),
      _state_dead(new GameStateDead(renderer, input, sound, this)),
      _state_finished(new GameStateFinished(renderer, input, sound, this)) {}

void Game::tick(ms tick_time) {
    // Set intial state - We need to set it here, not in constructor, because
    // it is called too early.
    if (!_current_state) set_state(INIT_STATE);
    _current_state->tick(tick_time);
    _current_state->next_state();
}

void Game::set_state(GameState *state) {
    if (_current_state) _current_state->exit();
    _current_state = state;
    _current_state->enter();
}
