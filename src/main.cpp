#include <Arduino.h>

#include <digitalWriteFast/digitalWriteFast.h>

// Defines for the shift register pins.
// CLOCK_IN and PS_IN must be interrupt pins
#define CLOCK_IN_PIN (2)
#define PS_IN_PIN (3)
#define DATA_OUT_PIN (1)
#define DATA_IN_PIN (0)

#define PARALLEL_INPUT_PIN_MODE (INPUT)

// The variable holding the actual bits that were read
using RegisterType = uint16_t;
constexpr RegisterType kHighBitMask = 0x8000; // Pattern where the highest bit of RegisterType is set
constexpr RegisterType kLowBitMask = 1U; // Pattern where the lowest bit of RegisterType is set
volatile RegisterType bits;

// Counters for debouncing the inputs
using CounterValueType = uint8_t; // Value-type for the counters
using CountersIndexType = uint8_t; // Type for the index of counters
constexpr CountersIndexType kNumCounters = sizeof(bits)*8;
volatile CounterValueType counters[kNumCounters];

void ClockISR() {
  uint8_t clockValue = digitalReadFast(CLOCK_IN_PIN);
  if (clockValue == HIGH) {
    // Rising edge. Write a new value to the output and shift the register
    digitalWriteFast(DATA_OUT_PIN, bits & kLowBitMask);
    bits >>= 1;
  } else {
    // Falling edge. Sample the input register.
    if (digitalReadFast(DATA_IN_PIN) == HIGH) {
      bits |= kHighBitMask;
    } // else {
      // bit was already zeroed by the shift operation
    // }
  }
}

void PSISR() {
  // Re-Read the bits
  
  // We use them as follows:
  // 15                  10  9                   4   3           0 
  // PC5 PC4 PC3 PC2 PC1 PC0 PB5 PB4 PB3 PB2 PB1 PB0 PD7 PD6 PD5 PD4
  // Thus, start with the lowest input bit at Digital 4 and go counter-clockwise
  // around the chip until you hit input 15 at pin A5.

  bits = ((uint16_t)PINC) << 10; // no mask needed, unused bits are shifted out
  bits |= ((uint16_t)(PINB & 0x3F)) << 4;
  bits |= PIND >> 4; // no mask needed, unused bits are shifted out
  digitalWriteFast(DATA_OUT_PIN, bits & kLowBitMask);
}

void setup() {
  // Reset all states
  bits = 0;
  for (CountersIndexType i = 0; i < kNumCounters; ++i) {
    counters[i] = 0;
  }

  // Configure the data pins. Set all remaining IO pins to input
  pinModeFast(4, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(5, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(6, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(7, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(8, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(9, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(10, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(11, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(12, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(13, PARALLEL_INPUT_PIN_MODE);

  pinModeFast(A0, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(A1, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(A2, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(A3, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(A4, PARALLEL_INPUT_PIN_MODE);
  pinModeFast(A5, PARALLEL_INPUT_PIN_MODE);

  // Configure the Interrupt and Data registers
  pinModeFast(CLOCK_IN_PIN, INPUT);
  pinModeFast(PS_IN_PIN, INPUT);
  pinModeFast(DATA_OUT_PIN, OUTPUT);
  pinModeFast(DATA_IN_PIN, INPUT);
  
  digitalWriteFast(DATA_OUT_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(CLOCK_IN_PIN), ClockISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PS_IN_PIN), PSISR, RISING);
}


void loop() {
  // put your main code here, to run repeatedly:
}