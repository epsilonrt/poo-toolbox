#pragma once

#include "twowiredevice.h"

class Pcf8574 : public TwoWireDevice {
  
  public:
    Pcf8574 (uint8_t slaveAddress = 0x20, TwoWire & bus = Wire);
    ~Pcf8574();
    
    bool begin();
        
    bool pinMode (int pin, int pinmode);
    int pinMode (int pin) const;
    bool write (int pin, bool bit);
    bool read (int pin);


    bool pinModes (uint8_t pinmodes);
    int pinModes () const;
    bool write (uint8_t value);
    uint8_t read();

  protected:
    bool write();
    
  private:
    int dir;
    int out;
};
