/*
  eeprom.h - Library for interfacing with 24LC32A EEPROM.
  Created by Aaron Wood, June 28, 2020.
  Released into the public domain.
*/

#ifndef I2Ceeprom_h
#define I2Ceeprom_h

#include "Arduino.h"

class I2Ceeprom
{
  public:
      I2Ceeprom(uint8_t chipAddress);
      int getData(uint16_t *timeStamp, uint16_t *reading);
      int writeData(uint16_t *timeStamp, uint16_t *reading);
      void printData(uint8_t address);
      int getNumDataPoints();
      int getNextAddress();
    private:
      uint8_t I2CAddress;
      void write16bit(uint16_t value);
};

#endif
