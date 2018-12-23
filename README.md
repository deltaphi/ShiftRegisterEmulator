# ShiftRegisterEmulator
An emulator for a 16-bit shift register. The behavior of this Sketch mimicks
the behavior of an S88 module (i.e., a chain of two 4014B Chips).
The Sketch is set up so that the Arduinos can be Daisy-Chained.

This project started because I needed a bunch of shift register inputs and had
lots of Atmega168 but no 4041B lying around.

The sketch does not use an external clock and does not use serial (almost all
IO pins are needed).

Upcoming Features:
* Correct reception of 16 input bits
* Debouncing of input pins over multiple reset-cycles
