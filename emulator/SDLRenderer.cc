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
    // Clear the drawing area
    SDL_SetRenderDrawColor(_renderer, 40, 40, 40, 255);
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
    int margin = 25, border = 1, spacing = 1;
    int row = 0, num_per_row = NUM_LEDS / 3;
    int side_width =
        ((width - (margin * 2) - (spacing * num_per_row)) / num_per_row);

    SDL_Rect rect{.y = margin,
                  .w = side_width - (2 * border),
                  .h = side_width - (2 * border)};
    SDL_Rect border_rect{
        .y = margin - border, .w = side_width, .h = side_width};
    for (uint16_t i = 0, col = 0; i < NUM_LEDS; i++) {
        row = i / num_per_row;
        col = i % num_per_row;

        // go zig zag from one row to the next
        if (row % 2 != 0) col = num_per_row - 1 - col;

        rect.y = margin + (rect.h * row) + ((border + spacing + border) * row);
        rect.x = margin + (rect.w * col) + ((border + spacing + border) * col);

        border_rect.y = rect.y - border;
        border_rect.x = rect.x - border;
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 150);
        SDL_RenderFillRect(_renderer, &border_rect);

        SDL_SetRenderDrawColor(_renderer, _leds[i].r, _leds[i].g, _leds[i].b,
                               150);
        SDL_RenderFillRect(_renderer, &rect);
    }
}
