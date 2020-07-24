#include <Wire.h>

#define CHIP_1 0x51
#define CHIP_2 0x53
#define CHIP_3 0x55
#define CHIP_4 0x57

#define LOW_MASK 0x00FF
#define HIGH_MASK 0xFF00

void setup() {
  char output[15];
  Wire.begin();
  Serial.begin(9600);
  for(uint16_t address = 0; address<0x100; address++){
    int i2cAddress;
    if(address < 0x1000){i2cAddress = CHIP_1;}
    else if(address < 0x2000){i2cAddress = CHIP_2;}
    else if(address < 0x3000){i2cAddress = CHIP_3;}
    else{i2cAddress = CHIP_4;}
    Wire.beginTransmission(i2cAddress);
    write16bit(address % 0x1000);
    Wire.endTransmission();
    delay(1);

    Wire.requestFrom(i2cAddress,1);
    uint8_t reading = Wire.read();
    sprintf(output,"%02x %03x  %02x",i2cAddress,address,reading);
    Serial.println(output);
  }
}

void write16bit(uint16_t value) //bigEndian
      {
          Wire.write((value & HIGH_MASK)>>8);
          Wire.write((value & LOW_MASK));
      }

void loop() {
  // put your main code here, to run repeatedly:

}
