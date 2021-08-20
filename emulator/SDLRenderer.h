#include "SDL.h"
#include "../common/Renderer.h"

class SDLRenderer final : public Renderer {
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    void handle_events();
public:
    SDLRenderer(uint16_t width, uint16_t height);
    ~SDLRenderer();
    virtual void clear() override;
    virtual void show() override;
};
