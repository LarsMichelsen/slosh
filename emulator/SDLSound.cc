#include "SDLSound.h"

const int AMPLITUDE = 60000;
const int FREQUENCY = 44100;

void audio_callback(void *_sound, uint8_t *_stream, int _length) {
    uint16_t *stream = (uint16_t *)_stream;
    int length = _length / 2;
    SDLSound *sound = (SDLSound *)_sound;

    sound->generate_samples(stream, length);
}

SDLSound::SDLSound() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0)
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

    SDL_AudioSpec desired_spec;

    desired_spec.freq = FREQUENCY;
    desired_spec.format = AUDIO_S16SYS;
    desired_spec.channels = 1;
    desired_spec.samples = 2048;
    desired_spec.callback = audio_callback;
    desired_spec.userdata = this;

    SDL_AudioSpec obtained_spec;

    // you might want to look for errors here
    if (SDL_OpenAudio(&desired_spec, &obtained_spec))
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s",
                     SDL_GetError());
    if (desired_spec.format != obtained_spec.format)
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO,
                     "Failed to get the desired AudioSpec");

    SDL_PauseAudio(0);
}

SDLSound::~SDLSound() { SDL_CloseAudio(); }

void SDLSound::play_note(uint16_t freq, uint8_t duration) {
    Beep beep;
    beep.freq = freq;
    beep.samples_left = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    _beeps.push(beep);
    SDL_UnlockAudio();
}

void SDLSound::generate_samples(uint16_t *stream, int length) {
    int i = 0;
    while (i < length) {
        if (_beeps.empty()) {
            while (i < length) {
                stream[i] = 0;
                i++;
            }
            return;
        }
        Beep &beep = _beeps.front();

        int left = std::min(i + beep.samples_left, length);
        beep.samples_left -= left - i;

        while (i < left) {
            stream[i] = AMPLITUDE * std::sin(_v * 2 * M_PI / FREQUENCY);
            i++;
            _v += beep.freq;
        }

        if (beep.samples_left == 0) _beeps.pop();
    }
}

// void SDLSound::wait() {
//    int size;
//    do {
//        SDL_Delay(20);
//        SDL_LockAudio();
//        size = _beeps.size();
//        SDL_UnlockAudio();
//    } while (size > 0);
//}
