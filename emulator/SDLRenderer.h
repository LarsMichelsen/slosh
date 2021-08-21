#include "../common/Renderer.h"
#include "SDL.h"

class SDLRenderer final : public Renderer {
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    void render_leds();

public:
    SDLRenderer(uint16_t width, uint16_t height);
    ~SDLRenderer();
    virtual void clear() override;
    virtual void show() override;
};
