#include <Arduino.h>

#include <digitalWriteFast/digitalWriteFast.h>

// Defines for the shift register pins.
// CLOCK_IN and PS_IN must be interrupt pins
#define CLOCK_IN_PIN (2)
#define PS_IN_PIN (3)
#define DATA_OUT_PIN (9)
#define DATA_IN_PIN (8)

// The variable holding the actual bits that were read
using RegisterType = uint8_t;
constexpr RegisterType kInputPattern = 0x80; // Pattern where the highest bit of RegisterType is set
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
    digitalWriteFast(DATA_OUT_PIN, bits & 0x01);
    bits >>= 1;
  } else {
    // Falling edge. Sample the input register.
    uint8_t inputValue = digitalReadFast(DATA_IN_PIN);
    if (inputValue == HIGH) {
      bits |= kInputPattern;
    }
  }
}

void PSISR() {
  // Re-Read the bits
  bits = PINC; // TODO: Select the correct bits 
  digitalWriteFast(DATA_OUT_PIN, bits & 0x01);
}

void setup() {
  // put your setup code here, to run once:
  bits = 0;
  for (CountersIndexType i = 0; i < kNumCounters; ++i) {
    counters[i] = 0;
  }

  // Configure the data pins
  pinModeFast(23, INPUT_PULLUP);
  pinModeFast(24, INPUT_PULLUP);
  pinModeFast(25, INPUT_PULLUP);
  pinModeFast(26, INPUT_PULLUP);
  pinModeFast(27, INPUT_PULLUP);
  pinModeFast(28, INPUT_PULLUP);

  // Configure the Interrupt and Data registers
  pinModeFast(CLOCK_IN_PIN, INPUT_PULLUP);
  pinModeFast(PS_IN_PIN, INPUT_PULLUP);
  pinModeFast(DATA_OUT_PIN, OUTPUT);
  pinModeFast(DATA_IN_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CLOCK_IN_PIN), ClockISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PS_IN_PIN), PSISR, RISING);
}


void loop() {
  // put your main code here, to run repeatedly:
}