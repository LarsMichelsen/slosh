
#include "Entity.h"

#include "GameStateLevel.h"
#include "Player.h"

Entity::Entity(GameStateLevel *level) : _level(level) {}

bool collides_during_move(pos_t from, pos_t to, pos_t check) {
    return check >= from && check <= to;
}

// Move the entity to a new position while checking the collision with other
// entities and give the object the option to trigger an action.
void Entity::move_to(pos_t pos) {
    pos_t low, high;
    if (get_position() > pos) {
        low = pos;
        high = get_position();
    } else {
        low = get_position();
        high = pos;
    }

    // TODO: Generalize the iteration over all entities
    if (this != dynamic_cast<Entity *>(_level->_player) &&
        _level->_player->is_spawned() &&
        collides_during_move(low, high, _level->_player->get_position())) {
        touches(_level->_player);
        if (!is_spawned()) return;
    }

    // Is there an enemy between the origin and the destination
    for (auto enemy : _level->_enemies) {
        if (this == &enemy) continue;
        if (!enemy.is_spawned()) continue;

        if (collides_during_move(low, high, enemy.get_position())) {
            touches(&enemy);
            if (!is_spawned()) return;
        }
    }

    if (_level->_exit->is_spawned() &&
        collides_during_move(low, high, _level->_exit->get_position())) {
        touches(_level->_exit);
        if (!is_spawned()) return;
    }

    set_position(pos);
}
