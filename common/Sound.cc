#include "Sound.h"

void Sound::play_attack(ms passed) {
    Note melody[] = {{587, 4}, {494, 4}, {587, 4}, {494, 4}, {587, 4}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 20, passed);
}

void Sound::play_enemy_died() { play_note(1046, 40); }

void Sound::play_player_died(ms passed) {
    Note melody[] = {{174, 4}, {87, 4}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_level_finished(ms passed) {
    Note melody[] = {{1046, 4}, {1175, 4}, {1046, 4}, {1762, 8}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_melody(Note* melody, uint8_t num_notes, uint8_t note_duration,
                        ms passed) {
    uint16_t index = passed / note_duration;
    if (index >= num_notes) {
        return;
    }
    if (index == _play_melody_last_index) return;  // Do not play a note twice
    _play_melody_last_index = index;
    if (melody[index].tone == 0) return;  // Do not play silence
    play_note(melody[index].tone, note_duration * melody[index].duration / 4);
}
