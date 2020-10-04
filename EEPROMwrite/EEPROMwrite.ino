#include <Wire.h>

#define CHIP_1 0x51
#define CHIP_2 0x53
#define CHIP_3 0x55
#define CHIP_4 0x57

#define LOW_MASK 0x00FF
#define HIGH_MASK 0xFF00

#define STACK_PTR_ADDRESS 0x0000
#define DATA_PT_COUNT_ADDRESS 0x0002
#define DATA_START 0x0004

void setup() {
  char output[15];
  Wire.begin();
  Serial.begin(9600);

  //  reset stack pointer
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  write16bit(DATA_START);
  Wire.endTransmission();
  delay(5);

  //reset number of data points
  Wire.beginTransmission(CHIP_1);
  write16bit(DATA_PT_COUNT_ADDRESS);
  write16bit(0x0000);
  Wire.endTransmission();
  delay(5);

  uint16_t address;
  do {
    Wire.beginTransmission(CHIP_1);
    write16bit(STACK_PTR_ADDRESS);
    Wire.endTransmission();
    delay(10);

    address = read16bit(STACK_PTR_ADDRESS);
    delay(10);
    //Serial.println(address == 0x0004);
    Wire.beginTransmission(CHIP_1);
    write16bit(address % 1000);
    write16bit(0x6666);
  } while (Wire.endTransmission());

  address+=2;
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  write16bit(address);
  Wire.endTransmission();
  
}

uint16_t read16bit(uint16_t address) //bigEndian
{
  int i2cAddress;
  if (address < 0x1000) {
    i2cAddress = CHIP_1;
  }
  else if (address < 0x2000) {
    i2cAddress = CHIP_2;
  }
  else if (address < 0x3000) {
    i2cAddress = CHIP_3;
  }
  else {
    i2cAddress = CHIP_4;
  }
  Wire.beginTransmission(i2cAddress);
  write16bit(address % 0x1000);
  Wire.endTransmission();

  Wire.requestFrom(i2cAddress, 2);
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  uint16_t result = msb;
  result = result << 8;
  result |= lsb;
  return (result);
}

void write16bit(uint16_t value) //bigEndian
{
  Wire.write((value & HIGH_MASK) >> 8);
  //Serial.println((value & HIGH_MASK)>>8);
  Wire.write((value & LOW_MASK));
  //Serial.println((value & LOW_MASK));
}
void loop() {
  // put your main code here, to run repeatedly:

}
