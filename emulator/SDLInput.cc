#include "SDLInput.h"

void SDLInput::handle_input(Player *player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        player->move(1);
                        break;
                    case SDLK_s:
                        player->move(-1);
                        break;
                    case SDLK_SPACE:
                        player->attack();
                        break;
                    case SDLK_ESCAPE:
                        exit(0);
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
