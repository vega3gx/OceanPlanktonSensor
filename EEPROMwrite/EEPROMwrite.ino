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
  

  Serial.println("done");
}

void write16bit(uint16_t value) //bigEndian
      {
          Wire.write((value & HIGH_MASK)>>8);
          //Serial.println((value & HIGH_MASK)>>8);
          Wire.write((value & LOW_MASK));
          //Serial.println((value & LOW_MASK));
      }
void loop() {
  // put your main code here, to run repeatedly:

}
