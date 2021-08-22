#include "Player.h"

#include "Game.h"

Player::Player(Game *game) : _game(game) {}

void Player::tick() {
    if (!is_spawned()) return;

    if (_attacking.attacking &&
        _game->time() - _attacking.time > _attack_duration)
        _attacking = {false, _game->time()};
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
    if (!_attacking.attacking) return;

    auto range = pos_to_led(_attack_range);
    auto pos = pos_to_led(get_position());
    for (auto i = pos - range; i < pos; i++) {
        renderer->set_led(i, 0, 0, 100);
    }

    for (auto i = pos + 1; i < pos + range + 1; i++) {
        renderer->set_led(i, 0, 0, 100);
    }
}

void Player::move(int8_t direction) {
    if (!is_spawned()) return;

    if ((int)get_position() + (int)(direction * _speed) < 0)
        move_to(0);
    else
        move_to(get_position() + (direction * _speed));
}

// Move the player to a new position while checking the collision with
// a hostile entity
void Player::move_to(uint16_t pos) {
    uint16_t low, high;
    if (get_position() > pos) {
        low = pos;
        high = get_position();
    } else {
        low = get_position();
        high = pos;
    }

    // Is there an enemy between the origin and the destination
    int num_enemies = sizeof(_game->_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++) {
        Enemy *e = &_game->_enemies[i];
        if (!e->is_spawned()) continue;

        if (e->get_position() - high <= high - low) {
            die();
            return;
        }
    }

    set_position(pos);
}

void Player::attack(bool wants_to_attack) {
    if (!is_spawned()) return;

    if (_attacking.attacking) return;  // Already attacking. Let it finish.

    if (_wants_to_attack) {
        // Prevent continous attacking. The user needs to release the attack
        // key once before a new attack can be started.
        if (!wants_to_attack) _wants_to_attack = false;
        return;
    }
    if (!wants_to_attack) return;  // Does not want to attack. Done.

    // New attack started
    _attacking = {true, _game->time()};
    _wants_to_attack = wants_to_attack;
}

// Whether or not the player is hitting the given entity with the attack
bool Player::is_attacking(Entity *entity) {
    return _attacking.attacking &&
           abs(get_position() - entity->get_position()) <= _attack_range;
}

void Player::die() { despawn(); }
