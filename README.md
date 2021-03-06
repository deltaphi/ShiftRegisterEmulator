# ShiftRegisterEmulator
An emulator for a 16-bit shift register. The behavior of this Sketch mimicks
the behavior of an S88 module (i.e., a chain of two 4014B Chips).
The Sketch is set up so that the Arduinos can be Daisy-Chained.

![PlatformIO CI](https://github.com/deltaphi/ShiftRegisterEmulator/workflows/PlatformIO%20CI/badge.svg?event=push)

## Hardware Notes

The sketch does not use serial (almost all IO pins are needed). It is set up
not to use the Oscillator Pins. The Sketch can thus be used both with an
external oscillator (e.g., Arduino Board) or without (e.g., Breadboard Setup).

Attempts have been made for a minimal parts setup, where the internal pullup
resistors are used. Thus, you would need only the Atmega and a pull-up resistor
for the reset pin. Unfortunately, I have had repeated trouble with the internal
pull-ups not working as expected (e.g., pulling *down* instead or being an
apparent short), so the default setup is to use external pullups.

In a 3.3V setting, the sketch works when you wire the Atmega up as follows:
* XTAL pins are left open
* All other pins are pulled high using 10k or 47k. Note that the DATA_OUT pin
  does not actually need a pull-up, but having one doesn't hurt functionality.

Note that you can conveniently use star-shaped resistor networks to pull all
pins high with only a few parts.

Note that I have not calculated the input current requirements on the shift
register pins. I use a 74HC367 current driver wired to an ESP32 to drive
the shift register.

### S88 Notes

Here is a not if you want to use this sketch to simulate an S88 module for your
model railroad. This sketch implements the latches of the 4044B chips on an S88
module in software. Therefore, it uses fewer lines. In S88 there are two lines
used for loading the register: "LOAD"/"PS" and "RESET". This sketch only uses
the "LOAD"/"PS" line.

At least on a 16 MHz Arduino, this sketch worked with the most agressive S88
timing I could find (~50us clock). Tests on an 8 MHz Arduino have not been
perfomed yet.

## Software Notes

This sketch was written with [PlatformIO](https://platformio.org/) using the
Arduino framework. It should easily be possible to build and upload it using
the Arduino IDE. You need to rename [src/main.cpp] to something with a
```.ino``` file extension and install the digitalWriteFast library in your
Arduino IDE (not available through the library manager, sadly).

## Why emulate a shift register?

This project started because I needed a bunch of shift register inputs and had
lots of Atmega168 but no 4041B lying around.

## Upcoming Features

* Correct reception of 16 input bits
* Debouncing of input pins over multiple reset-cycles
* Figure out whether using the internal pullups is a good idea (might overload
  the Atmegas' current capacity).

# Dependencies

This sketch uses the digitalWriteFast library (see git submodules).