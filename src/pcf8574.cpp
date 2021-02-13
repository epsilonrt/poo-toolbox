/* Copyright © 2021 Pascal JEAN, All rights reserved.
 * This file is part of the POO Toolbox Library.
 *
 * The POO Toolbox Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * The POO Toolbox Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the POO Toolbox Library; if not, see <http://www.gnu.org/licenses/>.
 */
#include "pcf8574.h"

// -----------------------------------------------------------------------------
//
//                            Pcf8574 class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Pcf8574::Pcf8574 (TwoWire & bus, uint8_t slaveAddress) :
  TwoWireDevice (slaveAddress, bus), dir (0xFF), out (0)  {
}

// -----------------------------------------------------------------------------
Pcf8574::Pcf8574 (uint8_t slaveAddress) :
  Pcf8574 (Wire, slaveAddress)  {
}

// -----------------------------------------------------------------------------
Pcf8574::~Pcf8574() {

  dir = 0xFF;
  write();
}

// -----------------------------------------------------------------------------
int Pcf8574::write () {

  if (isOpen()) {

    return TwoWireDevice::write (dir | (~dir & out));
  }
  return 0;
}

// -----------------------------------------------------------------------------
int Pcf8574::write (uint8_t value) {

  out = value & ~dir;
  return write();
}

// -----------------------------------------------------------------------------
int Pcf8574::read () {

  if (isOpen()) {
    
    return TwoWireDevice::read();
  }
  return 0;
}


// -----------------------------------------------------------------------------
int Pcf8574::digitalWrite (int pin, bool value) {

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
  return -1;
}

// -----------------------------------------------------------------------------
int Pcf8574::digitalRead (int pin) {
  int ret = -1;

  if (pin < 8) {

    ret = read();
    if (ret >= 0) {

      ret = ( ( (1 << pin) & ret) != 0);
    }
  }
  return ret;
}

// -----------------------------------------------------------------------------
bool Pcf8574::begin () {

  TwoWireDevice::begin();
  return (write() == 1);
}

// -----------------------------------------------------------------------------
int Pcf8574::pinModes (uint8_t pinmodes) {
  pinmodes = ~pinmodes;

  if (pinmodes != dir) {

    dir = pinmodes;
    return write();
  }
  return 0;
}

// -----------------------------------------------------------------------------
int Pcf8574::pinModes () const {

  return (unsigned) ~dir;
}

// -----------------------------------------------------------------------------
int Pcf8574::pinMode (int pin, int pinmode) {

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
  return -1;
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
