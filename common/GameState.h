#pragma once

#include "Input.h"
#include "Renderer.h"
#include "Sound.h"

class Game;

// Base class for the different game states
class GameState {
protected:
    Game* _game;
    Renderer* _renderer;
    Input* _input;

public:
    Sound* _sound;

    virtual void enter() = 0;
    virtual void tick(ms tick_time) = 0;
    virtual void exit() = 0;
    virtual void next_state() = 0;
    GameState(Renderer* renderer, Input* input, Sound* sound, Game* game)
        : _renderer(renderer), _input(input), _sound(sound), _game(game){};
    ~GameState(){};
};
