#include "Game.h"

#include "Input.h"
#include "Player.h"

Game::Game(Renderer *renderer, Input *input)
    : _input(input),
      _renderer(renderer),
      _player(new Player(this)),
      _exit(new Exit(this)),
      _enemies{Enemy(this), Enemy(this), Enemy(this), Enemy(this),
               Enemy(this)} {
    _level = load_level(0);
}

void Game::tick() {
    // Phase 0: Level switching
    if (!_player->is_spawned()) reload_level();
    if (_mark_level_finished) finish_level();

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

// Returns the milliseconds since start of the game
ms Game::time() { return get_ms() - _start_time; }

uint8_t Game::load_level(uint8_t level) {
    despawn_level();
    _mark_level_finished = false;
    switch (level) {
        case 1:
            _player->spawn(0);
            _enemies[0].spawn(100, Movement::None);
            _enemies[1].spawn(500, Movement::None);
            _enemies[2].spawn(800, Movement::None);
            return level;
        case 2:
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(400, Movement::UpAndDown);
            _enemies[2].spawn(700, Movement::UpAndDown);
            return level;
        case 3:
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(800, Movement::Down);
            return level;
        case 4:
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(400, Movement::UpAndDown);
            _enemies[2].spawn(600, Movement::Down);
            _enemies[3].spawn(800, Movement::Down);
            _enemies[4].spawn(950, Movement::Down);
            return level;
        case 0:
        default:
            _player->spawn(0);
            _enemies[2].spawn(300, Movement::None);
            return 0;
    }
}

bool Game::is_level_complete() {
    for (auto &enemy : _enemies)
        if (enemy.is_spawned()) return false;
    return true;
}

void Game::despawn_level() {
    // Despawn everything
    _player->despawn();
    for (auto &enemy : _enemies) enemy.despawn();
    _exit->despawn();
}

void Game::finish_level() {
    _level = load_level(_level + 1);  // Descend to next level
}

void Game::reload_level() { load_level(_level); }
