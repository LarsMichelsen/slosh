#include "Player.h"

#include "Enemy.h"
#include "GameStateLevel.h"

Player::Player(GameStateLevel *level) : Entity(level) {}

void Player::tick(ms tick_time) {
    if (!is_spawned()) return;

    if (_attacking.active && tick_time - _attacking.since > _attack_duration)
        _attacking = {false, tick_time};
    if (_attacking.active)
        _level->_sound->play_attack(tick_time - _attacking.since);
}

void Player::show(Renderer *renderer, ms tick_time) {
    if (!is_spawned()) return;

    show_player(renderer);
    show_attack(renderer, tick_time);
}

void Player::show_player(Renderer *renderer) {
    renderer->set_led(pos_to_led(get_position()), 100, 0, 100);
}

void Player::show_attack(Renderer *renderer, ms tick_time) {
    if (!_attacking.active) return;

    // Make it flicker synchronized with the sound
    uint8_t note_len = 20;
    uint8_t r = 0, g = 0, b = 255;
    if ((tick_time - _attacking.since) / note_len % 2 == 0) {
        g = 255;
        b = 0;
    }

    auto range = pos_to_led(_attack_range);
    auto pos = pos_to_led(get_position());
    for (auto i = pos - range; i < pos; i++) {
        renderer->set_led(i, r, g, b);
    }

    for (auto i = pos + 1; i < pos + range + 1; i++) {
        renderer->set_led(i, r, g, b);
    }
}

void Player::move(int8_t direction, ms tick_time) {
    if (!is_spawned()) return;

    bool wants_to_move = direction != 0;
    if (_moving.active != wants_to_move) _moving = {wants_to_move, tick_time};

    if (!_moving.active) return;

    // Add some acceleration to allow a) exact control and b) fast movement
    int move_duration = tick_time - _moving.since;
    int speed = _speed;
    if (move_duration < 600) {
        speed = _speed * (150 + move_duration) / 600;
    }

    int to = (int)get_position() + (int)(direction * speed);
    move_to(to < 0 ? 0 : to);
}

void Player::touches(Enemy *enemy) { die(); }
void Player::touches(Exit *exit) { _level->mark_finished(); }

void Player::attack(bool wants_to_attack, ms tick_time) {
    if (!is_spawned()) return;
    if (_wants_to_attack) {
        // Prevent continous attacking. The user needs to release the attack
        // key once before a new attack can be started.
        if (!wants_to_attack) _wants_to_attack = false;
        return;
    }
    if (_attacking.active) return;  // Already attacking. Let it finish.
    if (!_attacking.active && tick_time - _attacking.since < _attack_delay)
        return;                    // Cool down after an attack.
    if (!wants_to_attack) return;  // Does not want to attack. Done.

    // New attack started
    _attacking = {true, tick_time};
    _wants_to_attack = wants_to_attack;
}

// Whether or not the player is hitting the given entity with the attack
bool Player::is_attacking(Entity *entity) {
    return _attacking.active &&
           distance(get_position(), entity->get_position()) <= _attack_range;
}

void Player::die() { despawn(); }
