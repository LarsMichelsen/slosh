#include "Enemy.h"

Enemy::Enemy() {}

void Enemy::tick() {
    if (!is_spawned()) return;
}

void Enemy::show(Renderer *renderer) {
    if (!is_spawned()) return;

    uint16_t pos = pos_to_led(get_position());
    renderer->_leds[pos].r = 255;
    renderer->_leds[pos].g = 0;
    renderer->_leds[pos].b = 0;
}
