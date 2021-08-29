#include "Sound.h"

void Sound::play_attack(ms passed) {
    Note melody[] = {{587, 4}, {494, 4}, {587, 4}, {494, 4}, {587, 4}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 20, passed);
}

void Sound::play_enemy_died() { play_note(1046, 40); }
void Sound::play_spawner_died() { play_note(1762, 40); }
void Sound::play_spawner_spawned_enemy() { play_note(494, 40); }

void Sound::play_player_died(ms passed) {
    Note melody[] = {{174, 4}, {87, 4}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_level_finished(ms passed) {
    Note melody[] = {{1046, 4}, {1175, 4}, {1046, 4}, {1762, 8}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_init_phase0(ms passed) {
    Note melody[] = {
        {36, 4}, {30, 2}, {36, 4}, {41, 2}, {36, 4},
        {30, 2}, {36, 4}, {41, 2}, {0, 8},  {131, 8},
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_init_phase1(ms passed) {
    Note melody[] = {
        {131, 4}, {165, 4}, {175, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {440, 8},  //
        {131, 4}, {165, 4}, {440, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {175, 8},  //
        {131, 4}, {165, 4}, {175, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {440, 8},  //
        {131, 4}, {165, 4}, {440, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {175, 8},  //
        {131, 4}, {165, 4}, {175, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {440, 8},  //
        {131, 4}, {165, 4}, {440, 8}, {131, 4}, {165, 4}, {392, 8},
        {131, 4}, {165, 4}, {349, 8}, {131, 4}, {165, 4}, {330, 8},
        {131, 4}, {165, 4}, {220, 8}, {131, 4}, {165, 4}, {196, 8},
        {131, 4}, {165, 4}, {175, 8},  //
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_init_phase2(ms passed) {
    Note melody[] = {
        {36, 4}, {30, 2}, {36, 4}, {41, 2}, {36, 4},
        {30, 2}, {36, 4}, {41, 2}, {0, 8},  {131, 8},
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_won_phase0(ms passed) {
    Note melody[] = {
        {392, 4}, {330, 8}, {392, 4}, {330, 8}, {440, 4}, {494, 4}, {440, 4},
        {494, 4}, {523, 4}, {392, 8}, {523, 4}, {392, 8}, {587, 4}, {659, 4},
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 150, passed);
}

void Sound::play_game_won_phase1(ms passed) {
    Note melody[] = {
        {8, 16},  {8, 16},  {8, 16},  {8, 16},  {12, 16}, {12, 16},
        {12, 16}, {12, 16}, {32, 16}, {32, 16}, {32, 16}, {32, 16},
        {32, 16}, {32, 16}, {32, 16}, {32, 16}, {32, 16}, {32, 16},
        {32, 16}, {32, 16}, {32, 16}, {32, 16}, {32, 16}, {32, 16},
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_won_phase2(ms passed) {
    Note melody[] = {{5274, 16}, {5274, 16}, {7040, 16}, {7902, 16}};
    play_melody(melody, sizeof(melody) / sizeof(Note), 100, passed);
}

void Sound::play_game_won_phase3(ms passed) {
    Note melody[] = {
        {392, 4}, {330, 8}, {392, 4},  {330, 8}, {440, 4}, {494, 4},
        {440, 4}, {494, 4}, {523, 4},  {392, 8}, {523, 4}, {392, 8},
        {587, 4}, {659, 4}, {392, 4},  {330, 8}, {392, 4}, {330, 8},
        {440, 4}, {494, 4}, {440, 4},  //
        {494, 4}, {523, 4}, {392, 8},  {523, 4}, {392, 8}, {587, 4},
        {659, 4}, {392, 4}, {330, 8},  {392, 4}, {330, 8}, {440, 4},
        {494, 4}, {440, 4}, {494, 4},  {523, 4}, {392, 8}, {523, 4},
        {392, 8}, {587, 4}, {659, 4},  //
        {494, 4}, {523, 4}, {392, 8},  {523, 4}, {392, 8}, {587, 4},
        {659, 4}, {392, 4}, {330, 8},  {392, 4}, {330, 8}, {440, 4},
        {494, 4}, {440, 4}, {494, 4},  {523, 4}, {392, 8}, {523, 4},
        {392, 8}, {587, 4}, {659, 16},
    };
    play_melody(melody, sizeof(melody) / sizeof(Note), 200, passed);
}

void Sound::play_melody(Note* melody, uint8_t num_notes, uint8_t note_duration,
                        ms passed) {
    uint16_t index = passed / note_duration;
    if (index >= num_notes) {
        return;
    }
    if (index == _play_melody_last_index) return;  // Do not play a note twice
    _play_melody_last_index = index;
    play_note(melody[index].tone, note_duration * melody[index].duration / 4);
}

void Sound::play_game_won(ms passed) {}
