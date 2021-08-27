#include "BoardSound.h"

void BoardSound::play_note(uint16_t freq, uint8_t duration) {
    // Parameters:
    //   * frequency  - Play the specified frequency indefinitely, turn off with
    //   noToneAC().
    //   * volume     - [optional] Set a volume level. (default: 10, range: 0 to
    //   10 [0 = off])
    //   * length     - [optional] Set the length to play in milliseconds.
    //   (default: 0 [forever], range: 0 to 4294967295 [49.7 days])
    //   * background - [optional] Play note in background or pause till
    //   finished? (default: false, values: true/false)
    toneAC(freq, 10, duration, true);
}
