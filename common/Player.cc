#include "Player.h"

Player::Player() {}

void Player::tick() {
    if (!is_spawned()) return;
}

void Player::show(Renderer *renderer) {
    if (!is_spawned()) return;

    uint16_t pos = pos_to_led(get_position());
    renderer->_leds[pos].r = 128;
    renderer->_leds[pos].g = 128;
    renderer->_leds[pos].b = 128;
}

void Player::move(int8_t direction) {
    if ((int)get_position() + (int)(direction * _speed) < 0)
        set_position(0);
    else
        set_position(get_position() + (direction * _speed));
}

void Player::attack() {}
