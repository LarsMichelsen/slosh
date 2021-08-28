#include "GameStateLevel.h"

#include "Game.h"
#include "Player.h"

GameStateLevel::GameStateLevel(Renderer *renderer, Input *input, Sound *sound,
                               Game *game)
    : GameState(renderer, input, sound, game),
      _player(new Player(this)),
      _exit(new Exit(this)),
      _enemies{
          Enemy(this), Enemy(this), Enemy(this), Enemy(this),
          Enemy(this), Enemy(this), Enemy(this),
      },
      _spawners{Spawner(this)} {
    _level = load_level(INIT_LEVEL);
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

void GameStateLevel::tick(ms tick_time) {
    // Phase 1: Update the game logic.
    _input->handle_input(_player);
    _player->tick(tick_time);
    for (auto &enemy : _enemies) enemy.tick(tick_time);
    for (auto &spawner : _spawners) spawner.tick(tick_time);
    _exit->tick(tick_time);

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick(tick_time);

    _player->show(_renderer);
    for (auto &enemy : _enemies) enemy.show(_renderer);
    for (auto &spawner : _spawners) spawner.show(_renderer);
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
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(400, Movement::UpAndDown);
            _enemies[2].spawn(700, Movement::UpAndDown);
            return level;
        case 3:
            _player->spawn(0);
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
        case 5:
            _enemies[0].spawn(100, Movement::UpAndDown);
            _enemies[1].spawn(200, Movement::Up);
            _enemies[2].spawn(220, Movement::Up);
            _player->spawn(400);
            _enemies[3].spawn(580, Movement::Down);
            _enemies[4].spawn(600, Movement::Down);
            _enemies[5].spawn(900, Movement::UpAndDown);
            return level;
        case 6:
            _player->spawn(0);
            _enemies[0].spawn(50, Movement::Up);
            _enemies[1].spawn(200, Movement::UpAndDown);
            _enemies[2].spawn(210, Movement::UpAndDown);
            _enemies[3].spawn(220, Movement::UpAndDown);
            _enemies[4].spawn(230, Movement::UpAndDown);
            _enemies[5].spawn(240, Movement::UpAndDown);
            _enemies[6].spawn(800, Movement::Down);
            return level;
        case 7:
            _player->spawn(0);
            _spawners[0].spawn(600, 2500, Movement::Down);
            return level;
        case 0:
        default:
            _player->spawn(0);
            //_enemies[0].spawn(30);
            //_enemies[1].spawn(50, Movement::UpAndDown, 10);
            _enemies[0].spawn(300);
            return 0;
    }
}

// Whether or not all problems have been solved
bool GameStateLevel::is_complete() {
    for (auto &enemy : _enemies)
        if (enemy.is_spawned()) return false;
    for (auto &spawner : _spawners)
        if (spawner.is_spawned()) return false;
    return true;
}

// Return an Enemy pointer (or nullptr in case none is unspawned)
Enemy *GameStateLevel::get_unspawned_enemy() {
    for (auto &enemy : _enemies)
        if (!enemy.is_spawned()) return &enemy;
    return nullptr;
}

void GameStateLevel::despawn() {
    // Despawn everything
    _player->despawn();
    for (auto &enemy : _enemies) enemy.despawn();
    for (auto &spawner : _spawners) spawner.despawn();
    _exit->despawn();
}

void GameStateLevel::reload_level() { load_level(_level); }

// Returns the milliseconds since start of the level
ms GameStateLevel::time() { return get_ms() - _start_time; }
