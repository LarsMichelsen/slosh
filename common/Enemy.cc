#include "Enemy.h"

#include "Game.h"
#include "Player.h"

Enemy::Enemy(Game *game) : _game(game) {}

void Enemy::tick() {
    if (!is_spawned()) return;
    if (_game->_player->is_attacking(this)) {
        die();
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
