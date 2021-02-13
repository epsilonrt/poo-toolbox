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
#include "twowiredevice.h"

// -----------------------------------------------------------------------------
//
//                            TwoWireDevice class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
TwoWireDevice::TwoWireDevice (uint8_t slaveAddress, TwoWire & bus) :
  bus (bus), address (slaveAddress)  {
}

// -----------------------------------------------------------------------------
TwoWireDevice::~TwoWireDevice() {
  
  end();
}

// -----------------------------------------------------------------------------
int TwoWireDevice::read (uint8_t *values, uint16_t len) {
  int ret;

  ret = bus.requestFrom (address, len);
  if (ret > 0) {

    while (bus.available()) {

      *values++ = bus.read();
    }
  }
  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::read (uint8_t dataAddress, uint8_t *values, uint16_t len) {
  int ret = 0;

  bus.beginTransmission (address);
  ret = bus.write (dataAddress);

  if (ret == 1) {

    if (bus.endTransmission (false) == 0) {

      ret = this->read (values, len);
    }
    else {
      
      ret = -1;
    }
  }
  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::read (uint8_t dataAddress) {
  int ret;
  uint8_t data = 0xFF;

  ret = this->read (dataAddress, &data, 1);
  if (ret == 1) {
    ret = static_cast<unsigned> (data);
  }
  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::read () {
  int ret;
  uint8_t data = 0xFF;

  ret = this->read (&data, 1);
  if (ret == 1) {
    ret = static_cast<unsigned> (data);
  }
  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::write (const uint8_t *values, uint16_t len) {
  int ret;

  bus.beginTransmission (address);
  ret = bus.write (values, len);
  if (ret > 0) {

    if (bus.endTransmission() != 0) {

      ret = -1;
    }
  }
  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::write (uint8_t dataAddress, const uint8_t *values, uint16_t len) {
  int ret;

  bus.beginTransmission (address);

  ret = bus.write (dataAddress);
  if (ret == 1) {

    ret = bus.write (values, len);
    if (ret > 0) {

      if (bus.endTransmission() != 0) {

        ret = -1;
      }
    }
  }

  return ret;
}

// -----------------------------------------------------------------------------
int TwoWireDevice::write (uint8_t dataAddress, uint8_t value) {

  return this->write (dataAddress, &value, 1);
}

// -----------------------------------------------------------------------------
int TwoWireDevice::write (uint8_t value) {

  return this->write (&value, 1);
}

// -----------------------------------------------------------------------------
bool TwoWireDevice::begin() {

  bus.begin();
  return isOpen();
}

// -----------------------------------------------------------------------------
void TwoWireDevice::end() {

  bus.end();
}
