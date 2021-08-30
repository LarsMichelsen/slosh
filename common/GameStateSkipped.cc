#include "GameStateSkipped.h"

#include "Game.h"
#include "Player.h"
#include "utils.h"

GameStateSkipped::GameStateSkipped(Renderer *renderer, Input *input,
                                   Sound *sound, Game *game)
    : GameState(renderer, input, sound, game) {}

GameStateSkipped::~GameStateSkipped() {}

void GameStateSkipped::enter() {
    _start_time = get_ms();
    _finished = false;
}
void GameStateSkipped::exit() {}

void GameStateSkipped::next_state() {
    if (_finished) _game->set_state(_game->_state_level);
}

void GameStateSkipped::tick(ms tick_time) {
    ms duration = tick_time - _start_time;
    _sound->play_level_skipped(duration);

    _renderer->tick(tick_time);

    if (duration > 1000) {
        _finished = true;
        return;
    }

    pos_t player_pos = _game->_state_level->_player->get_position();
    if (duration % 2 == 0) {
        _renderer->set_led(pos_to_led(player_pos), 0, 255, 0);
    }
}
