/*
  eeprom.h - Library for interfacing with 24LC32A EEPROM.
  Created by Aaron Wood, June 28, 2020.
  Released into the public domain.
*/

#ifndef I2Ceeprom_h
#define I2Ceeprom_h

#define STACK_PTR_ADDRESS 0x000
#define DATA_PT_COUNT_ADDRESS 0x002
#define DATA_START 0x004

#define LOW_MASK 0x0FF
#define HIGH_MASK 0xF00

#include "Arduino.h"
#include <Wire.h>

      I2Ceeprom::I2Ceeprom(uint8_t chipAddress)
      {
        Wire.begin();
        I2CAddress = chipAddress;
        int error;
        do
        { //reset initial write position
          Wire.beginTransmission(chipAddress);
          write16bit(STACK_PTR);
          write16bit(DATA_START);
          error = Wire.endTransmission();
        }while(error);

        do
        {
          Wire.beginTransmission(chipAddress);
          Wire.write
          Wire.write((STACK_PTR & HIGH_MASK)>>8);
          Wire.write(STACK_PTR & LOW_MASK);
          Wire.write(DATA_START & HIGH_MASK)>>8);
          Wire.write(DATA_START & LOW_MASK);
          error = Wire.endTransmission();
        }
      }
      int getData(uint16_t *timeStamp, uint16_t *reading);
      int writeData(uint16_t *timeStamp, uint16_t *reading);
      void printData(uint8_t address);
      int getNumDataPoints();
      int getNextAddress();
      void write16bit(uint16_t value) //bigEndian
      {
          Wire.write((value & HIGH_MASK)>>8);
          Wire.write((value & LOW_MASK);
      }


#endif
