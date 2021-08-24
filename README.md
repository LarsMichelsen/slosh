# Slosh - Minimalistic one dimensional dungeon crawler

This project was inspired by [Twang](https://github.com/Critters/TWANG) and
[Line Wobbler](https://wobblylabs.com/projects/wobbler).

This project uses the same basic concepts:

* Minimalistic world: 1 RGB LED strip is the whole playground
* One joystick to control the player

However, I use a little different components than the other projects I have
seen so far:

* Arduino Mega
* 4 concatenated 144 per meter WS2128B strips
* 1 arcade joystick to control the player
* 1 speaker from broken headphones

## Software

The implementation of the game was made with a strip emulator I first built.
Thats why we basically have two applications:

* The emulator (cmake project in `emulator` directory)
* The Arduino application (PlatformIO project in `board` directory) which is
  built to run on the Arduino Mega.

The actual game is implemented in `common` directory and shared across both
applications.

The development environment was so far (but should not be limited to that):

* Ubuntu 20.04
* Clang 10, cmake for the emulator
* PlatformIO 5.1.1 for the board

### Build the emulator

First install the prerequisites (on Ubuntu):

```
sudo apt install cmake libsdl2-dev g++
```

You can then build the emulator like this:

```
git clone ...
cd emulator
cmake .
make
./emulator
```

### Emulator controls

When using the emulator, you use the keyboard for controls:

| Key    | Action |
| -------| -----|
| W      | Move up |
| S      | Move down |
| SPACE  | Attack |

### Board controls

You use the vertical axis for moving up and down the LED strip and the
horizontal axis for triggering the attack.

### Build the board firmware

This project uses `platformio` instead of the Arduino IDE for building the
board firmware. You should have the `platformio` command available in your
PATH.

```
git clone ...
cd board
./upload
```

Future ideas
------------

* Add multiplayer capabilities with 2nd joystick and other game mode

License
-------

It's the GPLv3. See [LICENSE](LICENSE) file.
