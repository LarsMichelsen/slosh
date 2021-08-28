#include "GameStateWon.h"

#include "Game.h"
#include "Player.h"
#include "utils.h"

GameStateWon::GameStateWon(Renderer *renderer, Input *input, Sound *sound,
                           Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateWon::~GameStateWon() {}

void GameStateWon::enter() {
    _start_time = get_ms();
    _finished = false;
}
void GameStateWon::exit() {}

void GameStateWon::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateWon::tick(ms tick_time) {
    ms duration = tick_time - _start_time;
    _sound->play_game_won(duration);

    _renderer->tick(tick_time);

    if (duration > 1000) {
        _finished = true;
        return;
    }
}
