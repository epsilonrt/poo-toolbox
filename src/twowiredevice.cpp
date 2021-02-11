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
uint8_t TwoWireDevice::read (uint8_t dataAddress, uint8_t *values, uint16_t len) {
  uint8_t readBytes = 0;
  bus.beginTransmission (address); // transmit to device
  bus.write (dataAddress);       // sends one uint8_t
  bus.endTransmission (false);   // repeat start transmitting
  readBytes += bus.requestFrom (address, len);   // request bytes from slave device
  while (bus.available()) { // slave may send less than requested
    *values++ = bus.read();    // receive a uint8_t as character
  }
  return readBytes;
}

// -----------------------------------------------------------------------------
uint8_t TwoWireDevice::read (uint8_t dataAddress) {
  uint8_t data = 0xFF;
  this->read (dataAddress, &data, 1);
  return data;
}

// -----------------------------------------------------------------------------
uint8_t TwoWireDevice::read (uint8_t *values, uint16_t len) {
  uint8_t readBytes = 0;
  bus.beginTransmission (address); // transmit to device
  readBytes += bus.requestFrom (address, len);   // request bytes from slave device
  while (bus.available()) { // slave may send less than requested
    *values++ = bus.read();    // receive a uint8_t as character
  }
  return readBytes;
}

// -----------------------------------------------------------------------------
uint8_t TwoWireDevice::read () {
  uint8_t data = 0xFF;
  this->read (&data, 1);
  return data;
}

// -----------------------------------------------------------------------------
bool TwoWireDevice::write (uint8_t dataAddress, const uint8_t *values, uint16_t len) {
  bus.beginTransmission (address); // transmit to device
  bus.write (dataAddress);       // sends one uint8_t
  bus.write (values, len);  // sends data bytes
  return (bus.endTransmission() == 0);    // stop transmitting
}

// -----------------------------------------------------------------------------
bool TwoWireDevice::write (uint8_t dataAddress, uint8_t value) {
  return this->write (dataAddress, &value, 1);
}

// -----------------------------------------------------------------------------
bool TwoWireDevice::write (const uint8_t *values, uint16_t len) {
  bus.beginTransmission (address); // transmit to device
  bus.write (values, len);  // sends data bytes
  return (bus.endTransmission() == 0);    // stop transmitting
}

// -----------------------------------------------------------------------------
bool TwoWireDevice::write (uint8_t value) {
  return this->write (&value, 1);
}
