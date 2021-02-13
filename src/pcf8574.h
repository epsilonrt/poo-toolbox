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
#pragma once

#include "twowiredevice.h"

#define P0 0
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5
#define P6 6
#define P7 7

/**
 * @class Pcf8574
 * @author Pascal JEAN
 * @date 02/11/21
 * @file pcf8574.h
 * @brief Remote 8-Bit I/O Expander for I2C Bus
 *
 * The I/O is defined as quasi-bidirectional. A quasi-bidirectional I/O is
 * either an input or output port without using a direction control register.
 * When set as inputs, the pins act as normal inputs do.  When set as outputs,
 * the PCF8574 device drives the outputs LOW with up to 25mA sink capability but
 * when driving the outputs HIGH, they are just pulled up high with a weak
 * internal pull-up.  That enables an external device to overpower the pin and
 * drive it LOW.
 *
 * The device powers up with the 8 data lines all set as inputs.
 *
 * When using the pins as inputs, the pins are set to HIGH by the MCU, which
 * turns on a weak 100 uA internal pull-up to Vcc. They will read as HIGH if
 * there is no input or if the pin is being driven HIGH by an external signal
 * but can be driven LOW by an external signal that can easily override the
 * weak pull-up.
 *
 * If used as outputs, they can be driven LOW by the MCU by writing a LOW to
 * that pin. A strong pull-down is turned on and stays on to keep the pin
 * pulled LOW. If the pin is driven HIGH by the MCU, a strong pull-up is turned
 * on for a short time to quickly pull the pin HIGH and then the weak 100uA
 * pull-up is turned back on to keep the pin HIGH.
 *
 * If the pins are set to be outputs and are driven LOW, it is important that an
 * external signal does not also try to drive it HIGH or excessive current may
 * flow and damage the part.
 *
 * Whenever the internal register is read, the value returned depends on the
 * actual voltage or status of the pin.
 *
 * The I/O ports are entirely independent of each other, but they are controlled
 * by the same read or write data byte.
 *
 * see https://www.ti.com/lit/ds/symlink/pcf8574.pdf
 */
class Pcf8574 : public TwoWireDevice {

  public:

    /**
     * @brief Default Constructor
     *
     * Uses the default I2C bus which depends on the target board used.
     *
     * @param slaveAddress 7-bit I²C slave address, right-aligned
     * this value depends on pins A0 to A2. The address of PCF8574 is 0100XXX,
     * with XXX = A2, A1, A0. If pins A2 to A0 are low, the address is
     * 0x20 (default).
     */
    Pcf8574 (uint8_t slaveAddress = 0x20);

    /**
     * @brief Constructor
     *
     * @param bus I²C bus to use
     * @param slaveAddress 7-bit I²C slave address, right-aligned
     * this value depends on pins A0 to A2. The address of PCF8574 is 0100XXX,
     * with XXX = A2, A1, A0. If pins A2 to A0 are low, the address is
     * 0x20 (default).
     */
    Pcf8574 (TwoWire & bus, uint8_t slaveAddress = 0x20);

    /**
     * @brief Destructor
     *
     * Return all pins to input (0xFF)
     */
    ~Pcf8574();

    /**
     * @brief Open the bus and configure all pins
     *
     * @return true, false if an error occurred, in this case error() allows
     * to read the error code
     */
    bool begin();

    /**
     * @brief Configures a pin as an input or an output
     *
     * Only pins configured as output can be changed by write().
     * All pins can be read.
     * @param pin pin number between 0 and 7 (P0 to P7)
     * @param pinmode pin mode, OUTPUT, INPUT or INPUT_PULLUP, as explained in
     * the datasheet, inputs P0 to P7 have a pull-up current, so there is no
     * difference between INPUT and INPUT_PULLUP.
     * @return 1 in case of success if bus open, 0 if stored bus closed, 
     * -1 if error.
     */
    int pinMode (int pin, int pinmode);

    /**
     * @brief Read pin mode
     * @param pin pin number between 0 and 7 (P0 to P7)
     * @return INPUT, OUTPUT, -1 if error 
     */
    int pinMode (int pin) const;

    /**
     * @brief Write a HIGH or a LOW value to a digital pin.
     * 
     * Only the pins configured as output see their state modified.
     * 
     * @param pin pin number between 0 and 7 (P0 to P7)
     * @param bit value, HIGH or LOW
     * @return 1 in case of success if bus open, 0 if stored bus closed, 
     * -1 if error.
     */
    int digitalWrite (int pin, bool bit);

    /**
     * @brief Reads the value from a specified digital pin
     * @param pin pin number between 0 and 7 (P0 to P7)
     * @return HIGH or LOW, -1 if error
     */
    int digitalRead (int pin);


    /**
     * @brief Configures all pins
     * @param pinmodes pin modes, the bit is high for an output, low for an input.
     * @return 1 in case of success if bus open, 0 if stored bus closed, 
     * -1 if error.
     */
    int pinModes (uint8_t pinmodes);

    /**
     * @brief Read all pin modes
     * @return pin modes, the bit is high for an output, low for an input, -1 if
     * error
     */
    int pinModes () const;

    /**
     * @brief Write all output pins
     * 
     * Only the pins configured as output see their state modified.
     * @param value bit 0 for P0 ... bit 7 for P7
     * @return 1 in case of success if bus open, 0 if stored bus closed, 
     * -1 if error.
     */
    int write (uint8_t value);

    /**
     * @brief Reads all pins
     * @return bit 0 for P0 ... bit 7 for P7, 0 if bus closed, -1 if error
     */
    int read();

  protected:
    /**
     * @brief Write current configuration 
     * @return 1 in case of success if bus open, 0 if stored bus closed, 
     * -1 if error.
     */
    int write();

  private:
    int dir;
    int out;
};
