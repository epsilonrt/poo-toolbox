#include "pcf8574.h"

// -----------------------------------------------------------------------------
//
//                            Pcf8574 class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Pcf8574::Pcf8574 (uint8_t slaveAddress, TwoWire & bus) :
  TwoWireDevice (slaveAddress, bus), dir (0xFF), out (0)  {
}

// -----------------------------------------------------------------------------
Pcf8574::~Pcf8574() {
  TwoWireDevice::write (0xFF);
}

// -----------------------------------------------------------------------------
bool Pcf8574::write () {
  return TwoWireDevice::write (dir | (~dir & out));
}

// -----------------------------------------------------------------------------
bool Pcf8574::write (uint8_t value) {
  out = value & ~dir;
  return write();
}

// -----------------------------------------------------------------------------
uint8_t Pcf8574::read() {
  return (TwoWireDevice::read() & dir) | (out & ~dir);
}

// -----------------------------------------------------------------------------
bool Pcf8574::begin () {
  return write();
}

// -----------------------------------------------------------------------------
bool Pcf8574::pinModes (uint8_t pinmodes) {
  pinmodes = ~pinmodes;

  if (pinmodes != dir) {
    dir = pinmodes;
    return write();
  }
  return true;
}

// -----------------------------------------------------------------------------
int Pcf8574::pinModes () const {
  return (unsigned) ~dir;
}

// -----------------------------------------------------------------------------
bool Pcf8574::set_mode (int pin, int pinmode) {

  if ( (pin < 8) &&
       ( (pinmode == OUTPUT) || (pinmode == INPUT) || (pinmode == INPUT_PULLUP))) {
    uint8_t pinmodes = pinModes();

    if (pinmode == OUTPUT) {

      pinmodes |= (1 << pin);
    }
    else {

      pinmodes &= ~ (1 << pin);
    }
    return pinModes (pinmodes);
  }
  return false;
}

// -----------------------------------------------------------------------------
int Pcf8574::pinMode (int pin) const {

  if (pin < 8) {

    if ( (1 << pin) & dir) {
      return INPUT;
    }
    return OUTPUT;
  }
  return -1;
}

// -----------------------------------------------------------------------------
bool Pcf8574::write (int pin, bool value) {

  if (pin < 8) {
    
    if (pinMode (pin) == OUTPUT) {
      
      if (value) {
        
        out |= 1 << pin;
      }
      else {

        out &= ~ (1 << pin);
      }
      return write();
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
bool Pcf8574::read (int pin) {
  
  if (pin < 8) {

    return ( (1 << pin) & read()) != 0;
  }
  return false;
}
