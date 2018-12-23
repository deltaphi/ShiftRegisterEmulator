# ShiftRegisterEmulator
An emulator for a 16-bit shift register. The behavior of this Sketch mimicks
the behavior of an S88 module (i.e., a chain of two 4014B Chips).
The Sketch is set up so that the Arduinos can be Daisy-Chained.

## Hardware Notes

The sketch does not use an external clock and does not use serial (almost all
IO pins are needed). Make sure to have your Atmega programmed to the internal
oscillator and an 8MHz clock.

### S88 Notes

Here is a not if you want to use this sketch to simulate an S88 module for your
model railroad. This sketch implements the latches of the 4044B chips on an S88
module in software. Therefore, it uses fewer lines. In S88 there are two lines
used for loading the register: "LOAD"/"PS" and "RESET". This sketch only uses
the "LOAD"/"PS" line.

At least on a 16 MHz Arduino, this sketch worked with the most agressive S88
timing I could find (~50us clock). Tests on an 8 MHz Arduino have not been
perfomed yet.

## Why emulate a shift register?

This project started because I needed a bunch of shift register inputs and had
lots of Atmega168 but no 4041B lying around.

## Upcoming Features

* Correct reception of 16 input bits
* Debouncing of input pins over multiple reset-cycles

# Dependencies

This sketch uses the digitalWriteFast library (see git submodules).