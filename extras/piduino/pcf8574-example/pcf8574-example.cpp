// Pcf8574 Demo

// Turns 5 LEDs on for one second, then off for one second, repeatedly.

// Created 16 March 2019

// This example code is in the public domain.
#ifdef __unix__
#include <Piduino.h>  // All the magic is here ;-)
#else
// Defines the serial port as the console on the Arduino platform
#define Console Serial
#endif

#include "pcf8574.h"

TwoWire Wire2; // the PCF8574 is connected on the i2c-2 bus
Pcf8574 pcf8574 (0x20, Wire2);

void setup() {
  
  Wire2.begin (2);
  pcf8574.begin();
  pcf8574.pinModes (0x1F); // 5 leds connected on pins P0 to P4
}

void loop () {
  
  // Press Ctrl+C to abort ...
  pcf8574.write (0xFF); // all leds off
  delay (1000);         // wait for a second
  pcf8574.write (0x00); // all leds on
  delay (1000);         // wait for a second
}
