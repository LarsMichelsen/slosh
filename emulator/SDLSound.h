#include <cmath>
#include <queue>

#include "../common/Sound.h"
#include "../common/utils.h"
#include "SDL.h"
#include "SDL_audio.h"
#include "stdint.h"

struct Beep {
    uint16_t freq;
    int samples_left;
};

class SDLSound final : public Sound {
private:
    double _v;
    std::queue<Beep> _beeps;

    virtual void play_note(uint16_t freq, uint8_t duration) override;
    // void wait();

public:
    SDLSound();
    ~SDLSound();
    void generate_samples(uint16_t *stream, int length);
};
