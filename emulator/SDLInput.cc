#include "SDLInput.h"

void SDLInput::handle_input(GameStateLevel *level, Player *player,
                            ms tick_time) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        player->move(1, tick_time);
                        break;
                    case SDLK_s:
                        player->move(-1, tick_time);
                        break;
                    case SDLK_l:
                        level->mark_skipped();
                        break;
                    case SDLK_SPACE:
                        player->attack(true, tick_time);
                        break;
                    case SDLK_ESCAPE:
                        exit(0);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        player->attack(false, tick_time);
                        break;
                    case SDLK_w:
                    case SDLK_s:
                        player->move(0, tick_time);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        exit(0);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}
