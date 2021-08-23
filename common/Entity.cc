
#include "Entity.h"

#include "Game.h"
#include "Player.h"

Entity::Entity(Game *game) : _game(game) {}

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
    if (this != dynamic_cast<Entity *>(_game->_player) &&
        _game->_player->is_spawned() &&
        collides_during_move(low, high, _game->_player->get_position())) {
        touches(_game->_player);
        if (!is_spawned()) return;
    }

    // Is there an enemy between the origin and the destination
    int num_enemies = sizeof(_game->_enemies) / sizeof(Enemy);
    for (uint8_t i = 0; i < num_enemies; i++) {
        Enemy *e = &_game->_enemies[i];
        if (this == e) continue;
        if (!e->is_spawned()) continue;

        if (collides_during_move(low, high, e->get_position())) {
            touches(e);
            if (!is_spawned()) return;
        }
    }

    if (_game->_exit->is_spawned() &&
        collides_during_move(low, high, _game->_exit->get_position())) {
        touches(_game->_exit);
        if (!is_spawned()) return;
    }

    set_position(pos);
}
