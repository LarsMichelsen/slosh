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
    SDL_Quit();
}

void SDLRenderer::clear() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
}

void SDLRenderer::show() {
    SDL_RenderPresent(_renderer);
}
