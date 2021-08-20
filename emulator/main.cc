#include "SDLRenderer.h"

int main(int argc, char *argv[])
{
    SDLRenderer renderer = SDLRenderer(80, 2000);
    renderer.clear();
    renderer.show();
    SDL_Delay(3000);
    return 0;
}
