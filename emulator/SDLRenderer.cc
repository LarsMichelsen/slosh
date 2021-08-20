#include <iostream>
#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(uint16_t width, uint16_t height) {
    SDL_Init(SDL_INIT_VIDEO);
    
    _window = SDL_CreateWindow(
      "Emulator",
      SDL_WINDOWPOS_CENTERED,
      50,
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
    this->render_leds();
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

void SDLRenderer::render_leds() {
    int width, height;
    SDL_GetWindowSize(_window, &width, &height);

    SDL_Rect rect;
    rect.y = 25;
    rect.w = width / NUM_LEDS;
    rect.h = width / NUM_LEDS;
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        if (_leds[i].r == 0 && _leds[i].g == 0 && _leds[i].b == 0)
            continue;

        rect.x = 25 + rect.w * i;
        SDL_SetRenderDrawColor(_renderer, _leds[i].r, _leds[i].g, _leds[i].b, 150);
        SDL_RenderFillRect(_renderer, &rect);
    }
}

