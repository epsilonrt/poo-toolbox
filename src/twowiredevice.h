#pragma once

#include <Arduino.h>
#include <Wire.h>

// I2c Slave Class
class TwoWireDevice {
  public:
    TwoWireDevice (uint8_t slaveAddress, TwoWire & bus = Wire);
    
    bool write (uint8_t value);
    uint8_t read();

    bool write (const uint8_t *values, uint16_t len);
    uint8_t read (uint8_t *values, uint16_t len);

    bool write (uint8_t dataAddress, uint8_t value);
    uint8_t read (uint8_t dataAddress);

    bool write (uint8_t dataAddress, const uint8_t *values, uint16_t len);
    uint8_t read (uint8_t dataAddress, uint8_t *values, uint16_t len);
    
    inline uint8_t get_address() const {
      return address;
    }
    inline void set_address (uint8_t slaveAddress) {
      address = slaveAddress;
    }
    inline TwoWire & get_bus() const {
      return bus;
    }
private:
    TwoWire & bus;
    uint8_t address;
};
