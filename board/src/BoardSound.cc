#include "BoardSound.h"

#define MAX_VOLUME 10

void BoardSound::play_note(uint16_t freq, uint8_t duration) {
    toneAC(freq, 10, duration, true);
}
