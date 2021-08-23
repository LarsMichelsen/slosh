#include "Enemy.h"

#include "Game.h"
#include "Player.h"

Enemy::Enemy(Game *game) : Entity(game) { init_movement(Movement::None); }

void Enemy::spawn(pos_t pos, Movement movement) {
    Entity::spawn(pos);
    init_movement(movement);
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

void Enemy::tick() {
    if (!is_spawned()) return;
    if (_game->_player->is_attacking(this)) die();
    move();
}

void Enemy::move() {
    if (_movement == Movement::None) return;

    // Controls the movement speed
    if (_next_move > _game->time()) return;
    _next_move = _game->time() + _move_delay;

    // Controls the movement pattern
    pos_t pos = get_position();
    switch (_movement) {
        case Movement::Down:
            move_to(pos - 1);
            break;
        case Movement::Up:
            move_to(pos + 1);
            break;
        case Movement::UpAndDown:
            if (_moving_down) {
                move_to(get_position() - 1);
                if (pos <= _spawn_position - _range) _moving_down = false;
            } else if (!_moving_down) {
                move_to(get_position() + 1);
                if (pos >= _spawn_position + _range) _moving_down = true;
            }
            break;
        default:
            break;
    }
}

void Enemy::show(Renderer *renderer) {
    if (!is_spawned()) return;

    uint16_t pos = pos_to_led(get_position());
    renderer->_leds[pos].r = 255;
    renderer->_leds[pos].g = 0;
    renderer->_leds[pos].b = 0;
}

void Enemy::die() { despawn(); };

void Enemy::touches(Player *player) {
    debug << "Enemy::touches(Player)\n";
    player->die();
};
