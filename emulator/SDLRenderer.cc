#include "SDLRenderer.h"

#include <iostream>

SDLRenderer::SDLRenderer(uint16_t width, uint16_t height) {
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("Emulator", SDL_WINDOWPOS_CENTERED, 50, width,
                               height, 0);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
}

SDLRenderer::~SDLRenderer() { SDL_DestroyWindow(_window); }

void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SDLRenderer::show() {
    clear();
    render_leds();
    SDL_RenderPresent(_renderer);
}

void SDLRenderer::render_leds() {
    int width, height;
    SDL_GetWindowSize(_window, &width, &height);

    SDL_Rect rect;
    rect.y = 25;
    rect.w = width / NUM_LEDS;
    rect.h = width / NUM_LEDS;
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        if (_leds[i].r == 0 && _leds[i].g == 0 && _leds[i].b == 0) continue;

        rect.x = 25 + rect.w * i;
        SDL_SetRenderDrawColor(_renderer, _leds[i].r, _leds[i].g, _leds[i].b,
                               150);
        SDL_RenderFillRect(_renderer, &rect);
    }
}
