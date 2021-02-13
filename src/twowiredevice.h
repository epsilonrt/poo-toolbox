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

#include <Arduino.h>
#include <Wire.h>

/**
 * @class TwoWireDevice
 * @author Pascal JEAN
 * @date 02/11/21
 * @file twowiredevice.h
 * @brief I²C integrated circuit
 * 
 * Allows write-read access to an I²C slave circuit
 */
class TwoWireDevice {
  public:

    /**
     * @brief Constructor
     * @param slaveAddress 7-bit I²C slave address, right-aligned
     * @param bus reference on the I²C bus to use
     */
    TwoWireDevice (uint8_t slaveAddress, TwoWire & bus = Wire);
    
    /**
     * @brief Destructor
     * 
     * call end()
     */
    ~TwoWireDevice();
    
    /**
     * @brief Open the I²C bus used
     */
    bool begin();
    
    /**
     * @brief Close the I²C bus used
     */
    void end();

    /**
     * @brief Write a byte in the integrated circuit
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit low, the \c value byte and a stop condition.
     * @param value byte to write
     * @return number of bytes written, -1 if error
     */
    int write (uint8_t value);

    /**
     * @brief Reading a byte in the integrated circuit
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit high, the byte read and a stop condition.
     * @return byte read as unsigned, -1 if error
     */
    int read();

    /**
     * @brief Write several bytes in the integrated circuit
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit low, the bytes to write and a stop condition.
     * @param values pointer to the bytes to write
     * @param number of bytes to write
     * @return number of bytes written, -1 if error
     */
    int write (const uint8_t *values, uint16_t len);

    /**
     * @brief Reading several bytes in the integrated circuit
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit high, the bytes read and a stop condition.
     * @param values pointer where to store bytes, must be able to store at least n bytes
     * @param number of bytes to read
     * @return number of bytes read, -1 if error
     */
    int read (uint8_t *values, uint16_t len);

    /**
     * @brief Write a byte in an integrated circuit register
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit low, the \c dataAddress, the \c value byte and a stop condition.
     * @param dataAddress register address or control byte
     * @param value byte to write
     * @return number of bytes written, -1 if error
     */
    int write (uint8_t dataAddress, uint8_t value);

    /**
     * @brief Reading a byte in an integrated circuit register
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit high, the \c dataAddress, the byte read and a stop condition.
     * @param dataAddress register address or control byte
     * @return byte read
     */
    int read (uint8_t dataAddress);

    /**
     * @brief Write bytes in integrated circuit registers
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit low, the \c dataAddress, the bytes to write and a stop condition.
     * @param dataAddress register address or control byte
     * @param values pointer to the bytes to write
     * @param number of bytes to write
     * @return number of bytes written, -1 if error
     */
    int write (uint8_t dataAddress, const uint8_t *values, uint16_t len);

    /**
     * @brief Reading several bytes in the integrated circuit
     *
     * The frame is made up of a start condition, the slave address with an
     * RW bit high, the \c dataAddress, the bytes read and a stop condition.
     * @param dataAddress register address or control byte
     * @param values pointer where to store bytes, must be able to store at least n bytes
     * @param number of bytes to read
     * @return number of bytes read, -1 if error
     */
    int read (uint8_t dataAddress, uint8_t *values, uint16_t len);

    /**
     * @brief Reading of the slave address of the integrated circuit
     * @return 7-bit I²C slave address, right-aligned
     */
    inline uint8_t get_address() const {
      
      return address;
    }
    
    /**
     * @brief Change of the slave address of the integrated circuit 
     * @param slaveAddress 7-bit I²C slave address, right-aligned
     */
    inline void set_address (uint8_t slaveAddress) {
      
      address = slaveAddress;
    }
    
    /**
     * @brief Returns the I²C bus used to access the integrated circuit
     * @return reference on the I²C bus used
     */
    inline TwoWire & get_bus() const {
      
      return bus;
    }

    /**
     * @brief Returns true if the I²C bus used is opened
     */
    inline bool isOpen() const {
      
      return bus.isOpen();
    }

  private:
    TwoWire & bus;
    uint8_t address;
};
