Slosh - Minimalistic one dimensional dungeon crawler
====================================================

This project was inspired by [Twang](https://github.com/Critters/TWANG) and
[Line Wobbler](https://wobblylabs.com/projects/wobbler).

This project uses the same basic concepts:

* Minimalistic world: 1 RGB LED strip is the whole playground
* One joystick to control the player

However, I used a little different components than the other projects

* Arduino Mega
* 4 concatenated 144 per meter WS2128B strips
* 1 arcade joystick to control the player

Software
--------

The basic implementation was made with a strip emulator I first built.  We
basically have two applications. The emulator (cmake project in `emulator`
directory) and the Arduino application which is built to run on the Arduino
Mega. The actual game is implemented in `common` directory and shared across
both applications.

The development environment was so far (but should not be limited to that):

* Ubuntu 20.04
* Arduino 1.8.15

You can build the emulator like this:

```sudo apt install cmake libsdl2-dev g++```

```
git clone ...
cd ../emulator
cmake .
make
./emulator
```

When using the emulator, you have the following controls:

| Key    | Action |
| -------| -----|
| W      | Move up |
| S      | Move down |
| SPACE  | Attack |

Future ideas
------------

* Add multiplayer capabilities with 2nd joystick and other game mode
