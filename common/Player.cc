#include "Player.h"

Player::Player() {}

void Player::tick() {
    if (!is_spawned()) return;
}

void Player::show(Renderer *renderer) {
    if (!is_spawned()) return;

    uint16_t pos = get_position();
    renderer->_leds[pos].r = 128;
    renderer->_leds[pos].g = 128;
    renderer->_leds[pos].b = 128;
}

void Player::move(int8_t direction) {
    set_position(clamp(get_position() + direction,
                       (int)std::numeric_limits<uint16_t>::lowest(),
                       (int)std::numeric_limits<uint16_t>::max()));
}

void Player::attack() {}
