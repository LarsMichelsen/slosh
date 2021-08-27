#pragma once

#include "utils.h"

struct Note {
    uint16_t tone;
    uint8_t duration;
};

// Abstract base for the sound
class Sound {
protected:
    virtual void play_note(uint16_t freq, uint8_t duration) = 0;
    void play_melody(Note* melody, uint8_t num_notes, uint8_t note_duration,
                     ms passed);

    uint8_t _player_died_last_index = 255;
    uint8_t _play_melody_last_index = 255;

public:
    void play_attack(ms passed);
    void play_enemy_died();
    void play_player_died(ms passed);
    void play_level_finished(ms passed);
    void play_game_init_phase0(ms passed);
    void play_game_init_phase1(ms passed);
    void play_game_init_phase2(ms passed);
};
