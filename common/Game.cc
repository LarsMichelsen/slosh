#include "Game.h"

#include "Input.h"
#include "Player.h"

Game::Game(Renderer *renderer, Input *input)
    : _input(input),
      _renderer(renderer),
      _player(new Player(this)),
      _enemies{Enemy(this), Enemy(this), Enemy(this), Enemy(this),
               Enemy(this)} {
    _player->spawn(0);
    _enemies[0].spawn(100);
    _enemies[1].spawn(500);
    _enemies[2].spawn(800);
}

void Game::tick() {
    // Phase 1: Update the game logic.
    _input->handle_input(_player);
    _player->tick();

    int num_enemies = sizeof(_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++) _enemies[i].tick();

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick();

    _player->show(_renderer);
    for (uint8_t i = 0; i < num_enemies; i++) _enemies[i].show(_renderer);
}

// Returns the milliseconds since start of the game
ms Game::time() { return get_ms() - _start_time; };
