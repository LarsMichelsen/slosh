#include "Exit.h"

#include "GameStateLevel.h"
#include "Player.h"

Exit::Exit(GameStateLevel *level) : Entity(level) {}

void Exit::tick(ms tick_time) {
    if (_level->is_complete() && !is_spawned()) spawn(WORLD_MAX);
}

void Exit::show(Renderer *renderer, ms tick_time) {
    if (!is_spawned()) return;
    renderer->set_led(pos_to_led(get_position()), 0, 255, 0);
}

void Exit::die(){};
