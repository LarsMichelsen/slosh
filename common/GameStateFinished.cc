#include "GameStateFinished.h"

#include "Game.h"
#include "Player.h"
#include "utils.h"

GameStateFinished::GameStateFinished(Renderer *renderer, Input *input,
                                     Sound *sound, Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateFinished::~GameStateFinished() {}

void GameStateFinished::enter() {
    _start_time = get_ms();
    _finished = false;
}
void GameStateFinished::exit() {}

void GameStateFinished::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateFinished::tick() {
    _sound->play_level_finished(get_ms() - _start_time);

    _renderer->tick();

    ms duration = get_ms() - _start_time;
    if (duration > 1000) {
        _finished = true;
        return;
    }

    pos_t player_pos = _game->_state_level->_player->get_position();
    if (duration % 2 == 0) {
        _renderer->set_led(pos_to_led(player_pos), 0, 255, 0);
    }
}
