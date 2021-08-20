#include <iostream>
#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(uint16_t width, uint16_t height) {
    SDL_Init(SDL_INIT_VIDEO);
    
    _window = SDL_CreateWindow(
      "SDL2Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      0
    );
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
}

SDLRenderer::~SDLRenderer() {
    SDL_DestroyWindow(_window);
}

void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
}

void SDLRenderer::show() {

    this->handle_events();
    SDL_RenderPresent(_renderer);
}

void SDLRenderer::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
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
