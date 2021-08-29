#include "Enemy.h"

#include "GameStateLevel.h"
#include "Player.h"

Enemy::Enemy(GameStateLevel *level) : Entity(level) {}

void Enemy::spawn(pos_t pos, Movement movement, ms move_delay, uint8_t speed) {
    Entity::spawn(pos);
    init_movement(movement);
    _move_delay = move_delay;
    _speed = speed;
}

// When setting a new movement mode, all movement related state vars need to
// be reinitialized.
// TODO: Choose a data structure that ensures this is done automatically.
void Enemy::init_movement(Movement movement) {
    _movement = movement;
    _next_move = 0;
    _spawn_position = get_position();

    // Movement::UpAndDown specific
    _moving_down = false;
    _range = 10;
}

void Enemy::tick(ms tick_time) {
    if (!is_spawned()) return;
    if (_level->_player->is_attacking(this)) {
        die();
        _level->_sound->play_enemy_died();
    }
    move(tick_time);
}

void Enemy::move(ms tick_time) {
    if (_movement == Movement::None) return;

    // Controls the movement speed
    if (_next_move > tick_time) return;
    _next_move = tick_time + _move_delay;

    // Controls the movement pattern
    pos_t pos = get_position();
    switch (_movement) {
        case Movement::Down:
            move_to(pos - _speed);
            if (pos - 1 == WORLD_MIN) _movement = Movement::Up;
            break;
        case Movement::Up:
            move_to(pos + _speed);
            if (pos + 1 == WORLD_MAX) _movement = Movement::Down;
            break;
        case Movement::UpAndDown:
            if (_moving_down) {
                move_to(pos - _speed);
                if (pos <= _spawn_position - _range || pos - 1 == WORLD_MIN) {
                    // debug << "turn up at " << pos << "\n";
                    _moving_down = false;
                }
            } else if (!_moving_down) {
                move_to(pos + _speed);
                if (pos >= _spawn_position + _range || pos + 1 == WORLD_MAX) {
                    // debug << "turn down at " << pos << "\n";
                    _moving_down = true;
                }
            }
            break;
        default:
            break;
    }
}

void Enemy::show(Renderer *renderer, ms tick_time) {
    if (!is_spawned()) return;
    renderer->_leds[pos_to_led(get_position())].set_rgb(255, 0, 0);
}

void Enemy::die() { despawn(); };
void Enemy::touches(Player *player) { player->die(); };
