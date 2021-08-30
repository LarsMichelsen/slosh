# Slosh - Minimalistic dungeon crawler 🚦🕹️

Have a look at the following twitter thread to get an idea what this is about.

<blockquote class="twitter-tweet" data-theme="light"><p lang="en" dir="ltr"><a href="https://twitter.com/hashtag/staycation?src=hash&amp;ref_src=twsrc%5Etfw">#staycation</a> simply rocks! 🤓🎉 building a minimalistic game played with the red clicky joystick on an RGB LED strip. <a href="https://t.co/gERPBq4jbG">pic.twitter.com/gERPBq4jbG</a></p>&mdash; Lars Michelsen (@LarsMichelsen) <a href="https://twitter.com/LarsMichelsen/status/1430218030727024641?ref_src=twsrc%5Etfw">August 24, 2021</a></blockquote>

## Hardware

The minimalistic playground is a *1 RGB LED strip* while the game is controlled with
a *clicky arcade joystick*.

I used the following components to build the game:

* Arduino Mega
* 4 concatenated 144 per meter WS2128B strips (removed plugs, soldered together)
* 1 arcade joystick to control the player
* 1 speaker from broken headphones (an old PC speaker will also work)
* 5V, 3A power supply (not enough to power on all LEDs at full brightness. But
  that is not needed at the moment anyway.)

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
* [PlatformIO](https://platformio.org/) 5.1.1 for the board

### Build the emulator

First install the prerequisites (on Ubuntu):

```
sudo apt install cmake libsdl2-dev g++
pip3 install -U platformio
```

You can then build the emulator like this:

```
git clone https://github.com/LarsMichelsen/slosh.git
cd slosh/emulator
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
| L      | Skip level |

### Board controls

You use the vertical axis for moving up and down the LED strip and the
horizontal axis for triggering the attack.

### Build the board firmware

This project uses `platformio` instead of the Arduino IDE for building the
board firmware. You should have the `platformio` command available in your
PATH. Then you should be able to build and upload it with the following
commands:

```
git clone https://github.com/LarsMichelsen/slosh.git
cd slosh/board
./upload
```

There is also a helper script `./deploy-loop` which continuously runs
`./upload`, then `./serial`. Once you hit `CTRL+C` while `serial` is running,
the script starts over with a new build.

## Wiring

The power supply `+` is connected to the Arduino VIN and the LED VIN.
The board is wired like this:

| PIN | Connected |
| ----| ----------|
| 2   | Joystick up |
| 3   | Joystick down |
| 4   | Joystick attack 1 |
| 5   | Joystick attack 2 |
| 6   | LED data |
| 7   | Skip level  |
| 11  | Speaker (as required by [ToneAC](https://github.com/teckel12/arduino-toneac)) |
| 12  | Speaker |

## License

It's the GPLv3. See [LICENSE](LICENSE) file.

## Thanks

This project was inspired by Robin Baumgarten's [Line Wobbler](https://wobblylabs.com/projects/wobbler) and [Twang](https://github.com/Critters/TWANG). Thanks for the inspiration! ✨
