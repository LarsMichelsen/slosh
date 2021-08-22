#include <chrono>
#include <csignal>
#include <ctime>
#include <thread>

#include "../common/Game.h"
#include "../common/utils.h"
#include "SDLInput.h"
#include "SDLRenderer.h"

void sigHandler(int signum) { exit(0); }

int main(int argc, char *argv[]) {
    signal(SIGINT, sigHandler);

    SDLRenderer renderer(3840, 90);
    SDLInput input;
    Game game(&renderer, &input);

    while (true) {
        auto start = std::chrono::system_clock::now();
        game.tick();
        renderer.show();
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed = end - start;

        while (elapsed < std::chrono::milliseconds(MS_PER_TICK)) {
            std::chrono::duration<double> wait_for =
                std::chrono::milliseconds(MS_PER_TICK) - elapsed;
            if (wait_for <= std::chrono::milliseconds(0)) break;
            std::this_thread::sleep_for(wait_for);
            elapsed = std::chrono::system_clock::now() - start;
        }
    }
    return 0;
}
