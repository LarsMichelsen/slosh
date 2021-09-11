#include "Spawner.h"

#include "GameStateLevel.h"
#include "Player.h"

Spawner::Spawner(GameStateLevel *level) : Entity(level) {}

Spawner *Spawner::spawn(pos_t pos, ms spawn_interval, Movement spawn_movement) {
    Entity::spawn(pos);
    _spawn_interval = spawn_interval;
    _spawn_movement = spawn_movement;
    _next_spawn = get_ms() + 10;
    return this;
}

void Spawner::tick(ms tick_time) {
    if (!is_spawned()) return;

    if (_level->_player->is_attacking(this)) {
        die();
        _level->_sound->play_spawner_died();
        return;
    }

    if (tick_time >= _next_spawn) {
        // Find an unspawned enemy. In case there is none free skip spawning.
        Enemy *enemy = _level->get_unspawned_enemy();
        if (enemy) {
            _level->_sound->play_spawner_spawned_enemy();
            enemy->spawn(get_position(), _spawn_movement);
        }
        _next_spawn = tick_time + _spawn_interval;
    }
}

void Spawner::show(Renderer *renderer, ms tick_time) {
    if (!is_spawned()) return;
    LED &led = renderer->_leds[pos_to_led(get_position())];
    uint8_t perc_interval = 100 * (_next_spawn - tick_time) / _spawn_interval;
    if (perc_interval > 100) perc_interval = 100;
    led.set_rgb(255 * perc_interval / 100, 165 * perc_interval / 100, 0);
}

void Spawner::die() {
    despawn();
    _level->count_killed_spawners();
};
