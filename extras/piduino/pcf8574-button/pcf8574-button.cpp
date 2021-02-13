// Pcf8574 Button Demo

// Turns on the led if the push button is pressed

// Created 13 Febrary 2021

// This example code is in the public domain.
#ifdef __unix__
#include <Piduino.h>  // All the magic is here ;-)
#else
// Defines the serial port as the console on the Arduino platform
#define Console Serial
#endif

#include "pcf8574.h"

TwoWire bus (2); // the PCF8574 is connected on the i2c-2 bus
Pcf8574 pcf8574 (bus);

const int Led = P0;
const int Sw = P5;

void setup() {

  pcf8574.pinMode (Led, OUTPUT);
  pcf8574.digitalWrite (Led, HIGH);

  pcf8574.pinMode (Sw, INPUT);

  if (! pcf8574.begin()) {

    Console.println ("Unable to connect to PCF8574, check wiring, slave address and bus id !");
    exit (EXIT_FAILURE);
  }
}

void loop () {

  // Press Ctrl+C to abort ...
  pcf8574.digitalWrite (Led, pcf8574.digitalRead (Sw));
  delay (10);
}
