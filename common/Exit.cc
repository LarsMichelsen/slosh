#include "Exit.h"

#include "GameStateLevel.h"
#include "Player.h"

Exit::Exit(GameStateLevel *level) : Entity(level) {}

void Exit::tick() {
    if (_level->is_level_complete() && !is_spawned()) spawn(WORLD_MAX);
}

void Exit::show(Renderer *renderer) {
    if (!is_spawned()) return;
    renderer->set_led(pos_to_led(get_position()), 0, 255, 0);
}

void Exit::die(){};
