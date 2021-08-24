#include "Sound.h"

void Sound::play_test() {
    uint16_t melody[] = {262, 196, 196, 220, 196, 0, 247, 262};
    uint8_t noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
    for (uint8_t thisNote = 0; thisNote < 8; thisNote++) {
        uint8_t noteDuration = 1000 / noteDurations[thisNote];
        // Play thisNote at full volume for noteDuration in the
        // background.
        play_note(melody[thisNote], noteDuration);
        // Wait while the tone plays in the background, plus
        // another 33% delay between notes.
        sleep_for(noteDuration * 4 / 3);
    }
}

void Sound::play_attack(ms duration, ms passed) {
    // Synchronized with the flicker animation
    uint8_t note_len = duration / 5;
    uint16_t melody[] = {587, 494, 587, 494, 587};
    uint8_t index = passed > 0 ? passed / note_len : 0;
    debug << passed << " " << note_len << " " << melody[index] << "\n";
    play_note(melody[index], note_len * 4 / 3);
}

void Sound::play_enemy_died() { play_note(1046, 40); }
