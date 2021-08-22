#include "Player.h"

Player::Player() {}

void Player::tick() {
    if (!is_spawned()) return;
}

void Player::show(Renderer *renderer) {
    if (!is_spawned()) return;

    uint16_t pos = pos_to_led(get_position());
    renderer->set_led(pos, 100, 0, 100);

    if (_attacking) {
        renderer->set_led(pos - 2, 0, 0, 100);
        renderer->set_led(pos - 1, 0, 0, 30);
        renderer->set_led(pos + 1, 0, 0, 30);
        renderer->set_led(pos + 2, 0, 0, 100);
    }
}

void Player::move(int8_t direction) {
    if ((int)get_position() + (int)(direction * _speed) < 0)
        set_position(0);
    else
        set_position(get_position() + (direction * _speed));
}

void Player::attack(bool attacking) { _attacking = attacking; }
