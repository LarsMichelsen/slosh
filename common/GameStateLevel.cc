#include "GameStateLevel.h"

#include "Game.h"
#include "Player.h"

GameStateLevel::GameStateLevel(Renderer *renderer, Input *input, Sound *sound,
                               Game *game)
    : GameState(renderer, input, sound, game),
      _player(new Player(this)),
      _exit(new Exit(this)),
      _enemies{Enemy(this), Enemy(this), Enemy(this), Enemy(this),
               Enemy(this)} {
    _level = load_level(0);
}

GameStateLevel::~GameStateLevel() {
    delete _player;
    delete _exit;
}

void GameStateLevel::enter() {
    if (_mark_finished)
        _level = load_level(_level + 1);  // Descend to next level
    else if (!_player->is_spawned())
        reload_level();
}
void GameStateLevel::exit() { despawn(); }

void GameStateLevel::next_state() {
    if (!_player->is_spawned()) _game->set_state(_game->_state_dead);
    if (_mark_finished) _game->set_state(_game->_state_finished);
}

void GameStateLevel::tick() {
    // Phase 1: Update the game logic.
    _input->handle_input(_player);
    _player->tick();
    for (auto &enemy : _enemies) enemy.tick();
    _exit->tick();

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick();

    _player->show(_renderer);
    for (auto &enemy : _enemies) enemy.show(_renderer);
    _exit->show(_renderer);
}
uint8_t GameStateLevel::load_level(uint8_t level) {
    despawn();
    _mark_finished = false;
    switch (level) {
        case 1:
            _player->spawn(0);
            _enemies[0].spawn(100);
            _enemies[1].spawn(500);
            _enemies[2].spawn(800);
            return level;
        case 2:
            _player->spawn(0);
            _enemies[0].spawn(200)->moving(Movement::UpAndDown);
            _enemies[1].spawn(400)->moving(Movement::UpAndDown);
            _enemies[2].spawn(700)->moving(Movement::UpAndDown);
            return level;
        case 3:
            _player->spawn(0);
            _enemies[0].spawn(200)->moving(Movement::UpAndDown);
            _enemies[1].spawn(800)->moving(Movement::Down);
            return level;
        case 4:
            _player->spawn(0);
            _enemies[0].spawn(200)->moving(Movement::UpAndDown);
            _enemies[1].spawn(400)->moving(Movement::UpAndDown);
            _enemies[2].spawn(600)->moving(Movement::Down);
            _enemies[3].spawn(800)->moving(Movement::Down);
            _enemies[4].spawn(950)->moving(Movement::Down);
            return level;
        case 0:
        default:
            _player->spawn(0);
            //_enemies[0].spawn(30);
            //_enemies[1].spawn(50)->moving(Movement::UpAndDown, 10);
            _enemies[0].spawn(300);
            return 0;
    }
}

// Whether or not all problems have been solved
bool GameStateLevel::is_complete() {
    for (auto &enemy : _enemies)
        if (enemy.is_spawned()) return false;
    return true;
}

void GameStateLevel::despawn() {
    // Despawn everything
    _player->despawn();
    for (auto &enemy : _enemies) enemy.despawn();
    _exit->despawn();
}

void GameStateLevel::reload_level() { load_level(_level); }

// Returns the milliseconds since start of the level
ms GameStateLevel::time() { return get_ms() - _start_time; }
