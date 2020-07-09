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
    int getData(uint16_t address, uint16_t *timeStamp, uint16_t *reading);
    int writeData(uint16_t address, uint16_t *timeStamp, uint16_t *reading);
  private:
    int readByte(uint16_t address, uint8_t *data);
    int writeByte(uint16_t address, uint8_t *data);
};

#endif
