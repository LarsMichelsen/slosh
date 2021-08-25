#include "Player.h"

#include "Enemy.h"
#include "GameStateLevel.h"

Player::Player(GameStateLevel *level) : Entity(level) {}

void Player::tick() {
    if (!is_spawned()) return;

    if (_attacking.active &&
        _level->time() - _attacking.since > _attack_duration)
        _attacking = {false, _level->time()};
    if (_attacking.active)
        _level->_sound->play_attack(_attack_duration,
                                    _level->time() - _attacking.since);
}

void Player::show(Renderer *renderer) {
    if (!is_spawned()) return;

    show_player(renderer);
    show_attack(renderer);
}

void Player::show_player(Renderer *renderer) {
    renderer->set_led(pos_to_led(get_position()), 100, 0, 100);
}

void Player::show_attack(Renderer *renderer) {
    if (!_attacking.active) return;

    // Make it flicker synchronized with the sound
    uint8_t note_len = 100 / 5;
    uint8_t r = 0, g = 0, b = 255;
    if ((_level->time() - _attacking.since) / note_len % 2 == 0) {
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

void Player::move(int8_t direction) {
    if (!is_spawned()) return;

    bool wants_to_move = direction != 0;
    if (_moving.active != wants_to_move)
        _moving = {wants_to_move, _level->time()};

    if (!_moving.active) return;

    // Add some acceleration to allow a) exact control and b) fast movement
    int move_duration = _level->time() - _moving.since;
    int speed = _speed;
    if (move_duration < 600) {
        speed = _speed * (150 + move_duration) / 600;
    }

    int to = (int)get_position() + (int)(direction * speed);
    move_to(to < 0 ? 0 : to);
}

void Player::touches(Enemy *enemy) {
    debug << "Player::touches(Enemy)\n";
    die();
}
void Player::touches(Exit *exit) {
    debug << "Player::touches(Exit)\n";
    _level->mark_level_finished();
}

void Player::attack(bool wants_to_attack) {
    if (!is_spawned()) return;

    if (_attacking.active) return;  // Already attacking. Let it finish.

    if (_wants_to_attack) {
        // Prevent continous attacking. The user needs to release the attack
        // key once before a new attack can be started.
        if (!wants_to_attack) _wants_to_attack = false;
        return;
    }
    if (!wants_to_attack) return;  // Does not want to attack. Done.

    // New attack started
    _attacking = {true, _level->time()};
    _wants_to_attack = wants_to_attack;
}

// Whether or not the player is hitting the given entity with the attack
bool Player::is_attacking(Entity *entity) {
    // Please note: Needs to be done before abs() call.
    // See https://www.arduino.cc/reference/de/language/functions/math/abs/
    int dist = (int)get_position() - (int)entity->get_position();
    // debug << "Attacking " << _attacking.active << "dist " << abs(dist)
    //      << " range: " << _attack_range << "\n";
    return _attacking.active && abs(dist) <= _attack_range;
}

void Player::die() { despawn(); }
