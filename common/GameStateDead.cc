#include "GameStateDead.h"

#include "Game.h"
#include "Player.h"
#include "utils.h"

GameStateDead::GameStateDead(Renderer *renderer, Input *input, Sound *sound,
                             Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateDead::~GameStateDead() {}

void GameStateDead::enter() {
    _start_time = get_ms();
    _finished = false;
}
void GameStateDead::exit() {}

void GameStateDead::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateDead::tick() {
    _sound->play_player_died(500, get_ms() - _start_time);
    _renderer->tick();

    ms duration = get_ms() - _start_time;
    if (duration > 500) {
        _finished = true;
        return;
    }

    pos_t player_pos = _game->_state_level->_player->get_position();
    if (duration % 2 == 0) {
        _renderer->set_led(pos_to_led(player_pos), 255, 0, 0);
    }
}
