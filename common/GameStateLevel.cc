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

void GameStateLevel::enter() { reload_level(); }
void GameStateLevel::exit() { despawn_level(); }

void GameStateLevel::tick() {
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
uint8_t GameStateLevel::load_level(uint8_t level) {
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
            _enemies[0].spawn(2, Movement::None);
            _enemies[2].spawn(300, Movement::None);
            return 0;
    }
}

bool GameStateLevel::is_level_complete() {
    for (auto &enemy : _enemies)
        if (enemy.is_spawned()) return false;
    return true;
}

void GameStateLevel::despawn_level() {
    // Despawn everything
    _player->despawn();
    for (auto &enemy : _enemies) enemy.despawn();
    _exit->despawn();
}

void GameStateLevel::finish_level() {
    _level = load_level(_level + 1);  // Descend to next level
}

void GameStateLevel::reload_level() { load_level(_level); }

// Returns the milliseconds since start of the level
ms GameStateLevel::time() { return get_ms() - _start_time; }