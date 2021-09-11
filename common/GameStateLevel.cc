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
      _spawners{Spawner(this), Spawner(this)} {
    _level = load_level(INIT_LEVEL);
}

GameStateLevel::~GameStateLevel() {
    delete _player;
    delete _exit;
}

void GameStateLevel::enter() {
    if (_mark_finished || _mark_skipped)
        load_next_level();
    else if (!_player->is_spawned())
        reload_level();
}
void GameStateLevel::exit() { despawn(); }

void GameStateLevel::next_state() {
    if (!_player->is_spawned()) _game->set_state(_game->_state_dead);
    if (_mark_finished) _game->set_state(_game->_state_finished);
    if (_mark_skipped) _game->set_state(_game->_state_skipped);
    if (_mark_won) _game->set_state(_game->_state_won);
}

void GameStateLevel::tick(ms tick_time) {
    // Phase 1: Update the game logic.
    _input->handle_input(this, _player, tick_time);
    _player->tick(tick_time);
    for (auto &enemy : _enemies) enemy.tick(tick_time);
    for (auto &spawner : _spawners) spawner.tick(tick_time);
    tick_level(tick_time);
    _exit->tick(tick_time);

    // Phase 2: Render the objects for the user and write it to the
    // world representing `_renderer->_leds` data structure.
    _renderer->tick(tick_time);

    _player->show(_renderer, tick_time);
    for (auto &enemy : _enemies) enemy.show(_renderer, tick_time);
    for (auto &spawner : _spawners) spawner.show(_renderer, tick_time);
    _exit->show(_renderer, tick_time);
}

uint8_t GameStateLevel::load_level(uint8_t level) {
    despawn();
    _num_killed_enemies = 0;
    _num_killed_spawners = 0;
    _mark_finished = false;
    _mark_won = false;
    _mark_skipped = false;
    switch (level) {
        case 1:
            // Three standing enemies
            _player->spawn(0);
            _enemies[0].spawn(100);
            _enemies[1].spawn(500);
            _enemies[2].spawn(800);
            return level;
        case 2:
            // Introducing up and down moving enemies
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(400, Movement::UpAndDown);
            _enemies[2].spawn(700, Movement::UpAndDown);
            return level;
        case 3:
            // Mixed movements
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(800, Movement::Down);
            return level;
        case 4:
            // Mixed movements
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown);
            _enemies[1].spawn(400, Movement::UpAndDown);
            _enemies[2].spawn(600, Movement::Down);
            _enemies[3].spawn(800, Movement::Down);
            _enemies[4].spawn(950, Movement::Down);
            return level;
        case 5:
            // Player spawning in the middle, mixed movements
            _enemies[0].spawn(100, Movement::UpAndDown);
            _enemies[1].spawn(200, Movement::Up);
            _enemies[2].spawn(220, Movement::Up);
            _player->spawn(400);
            _enemies[3].spawn(580, Movement::Down);
            _enemies[4].spawn(600, Movement::Down);
            _enemies[5].spawn(900, Movement::UpAndDown);
            return level;
        case 6:
            // Mixed movements
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
            // Introducing spawners
            _player->spawn(0);
            _spawners[1].spawn(600, 2500, Movement::Down);
            return level;
        case 8:
            // 3 enemies following the player once in range
            _player->spawn(0);
            _enemies[0].spawn(200, Movement::UpAndDown, 60, 1, 20);
            _enemies[1].spawn(400, Movement::UpAndDown, 60, 1, 30);
            _enemies[2].spawn(600, Movement::UpAndDown, 60, 2, 40);
            return level;
        case 9:
            // Extremely fast enemies
            _enemies[0].spawn(200, Movement::Up, 0, 2);
            _player->spawn(300);
            _enemies[1].spawn(400, Movement::Down, 0, 2);
            _enemies[2].spawn(410, Movement::Down, 0, 2);
            _enemies[3].spawn(440, Movement::Down, 0, 2);
            return level;
        case 0:
        default:
            // The first enemy
            _player->spawn(0);
            _enemies[0].spawn(300);
            return 0;
    }
}

// Level specific dynamic logic
void GameStateLevel::tick_level(ms tick_time) {
    if (_level == 7) {
        if (_num_killed_spawners == 1 && !_spawners[0].is_spawned()) {
            _spawners[0].spawn(400, 2500, Movement::Up);
        } else if (_num_killed_spawners == 2) {
            if (!_spawners[0].is_spawned())
                _spawners[0].spawn(600, 2500, Movement::Down);
            if (!_spawners[1].is_spawned() && _player->get_position() > 500)
                _spawners[1].spawn(400, 2500, Movement::Up);
        } else if (_num_killed_spawners == 4 && !_spawners[0].is_spawned() &&
                   _player->get_position() > 950) {
            _spawners[0].spawn(900, 2500, Movement::Up);
        }
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

void GameStateLevel::load_next_level() { _level = load_level(_level + 1); }
void GameStateLevel::reload_level() { load_level(_level); }
