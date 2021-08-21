#include  "Game.h"

Game::Game(Renderer *renderer, Input *input) {
    _input = input;
    _renderer = renderer;
    _player = new Player();
    _player->spawn();
}

Game::~Game() {
    delete _player;
}

void Game::tick() {
    // Phase 1: Update the game logic.
    _input->handle_input(_player);
    _player->tick();

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick();
    _player->show(_renderer);
}
