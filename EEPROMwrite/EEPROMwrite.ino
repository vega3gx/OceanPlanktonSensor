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
  Serial.println("Begin Erasing");
  for(uint16_t address = 0; address<0x100; address+=2){
    int i2cAddress;
    if(address < 0x1000){i2cAddress = CHIP_1;}
    else if(address < 0x2000){i2cAddress = CHIP_2;}
    else if(address < 0x3000){i2cAddress = CHIP_3;}
    else{i2cAddress = CHIP_4;}
    Wire.beginTransmission(i2cAddress);
    Serial.println("Address");
    write16bit(address);
    Serial.println("data");
    write16bit(0x8138);
    Wire.endTransmission();
    delay(5);
  }
//    uint8_t reading;
//    do
//    {
//      Wire.beginTransmission(0x50);
//      Wire.write((0x000&0xF00)>>8);
//      Wire.write(0x000&0x0FF);
//      Wire.write(0x00);
//      error = Wire.endTransmission();
//
//      Wire.beginTransmission(0x50);
//      Wire.write(0x00);
//      Wire.write(0x00);
//      Wire.endTransmission();
//
//      delay(1);
//
//      Wire.requestFrom(0x50,1);
//      reading = Wire.read();
//    }while(error || reading);
//    Wire.requestFrom(0x50,1);
//    int reading = Wire.read();
//    sprintf(output,"%03x  %02x",address,reading);
//    Serial.println(output);
  Serial.println("done");
}

void write16bit(uint16_t value) //bigEndian
      {
          Wire.write((value & HIGH_MASK)>>8);
          Serial.println((value & HIGH_MASK)>>8);
          Wire.write((value & LOW_MASK));
          Serial.println((value & LOW_MASK));
      }
void loop() {
  // put your main code here, to run repeatedly:

}
