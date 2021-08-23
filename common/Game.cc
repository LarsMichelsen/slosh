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
    // Phase 1: Update the game logic.
    _input->handle_input(_player);
    _player->tick();

    int num_enemies = sizeof(_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++) _enemies[i].tick();

    _exit->tick();

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick();

    _player->show(_renderer);
    for (uint8_t i = 0; i < num_enemies; i++) _enemies[i].show(_renderer);
    _exit->show(_renderer);
}

// Returns the milliseconds since start of the game
ms Game::time() { return get_ms() - _start_time; }

uint8_t Game::load_level(uint8_t level) {
    switch (level) {
        case 1:
            _player->spawn(0);
            _enemies[0].spawn(100);
            _enemies[1].spawn(500);
            _enemies[2].spawn(800);
            return level;
        case 0:
        default:
            _player->spawn(0);
            _enemies[0].spawn(200);
            return 0;
    }
}

bool Game::is_level_complete() {
    int num_enemies = sizeof(_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++)
        if (_enemies[i].is_spawned()) return false;
    return true;
}

void Game::finish_level() {
    // Despawn everything
    _player->despawn();

    int num_enemies = sizeof(_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++) _enemies[i].despawn();

    _exit->despawn();

    // Descend to next level
    _level = load_level(_level + 1);
}
