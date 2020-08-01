#include <Wire.h>

#define CHIP_1 0x51
#define CHIP_2 0x53
#define CHIP_3 0x55
#define CHIP_4 0x57


#define STACK_PTR_ADDRESS 0x0000
#define DATA_PT_COUNT_ADDRESS 0x0002
#define DATA_START 0x0004

#define LOW_MASK 0x00FF
#define HIGH_MASK 0xFF00

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Logging Begin");
  I2CeepromInit();
  Wire.beginTransmission(CHIP_1);
  write16bit(DATA_PT_COUNT_ADDRESS);
  write16bit(0);
  Wire.endTransmission();
}

void loop() {
  //Serial.println("Hello World");
  // put your main code here, to run repeatedly:
  for(uint16_t i = 1; i!=0; i = i<<1){
    writeEEPROMData(0x6969);
    //Serial.println(i);
    delay(1000);
  }
}

void I2CeepromInit(){
  Wire.begin();
  int error;
  do
  { //reset initial write position
    Wire.beginTransmission(CHIP_1);
    write16bit(STACK_PTR_ADDRESS);
    write16bit(DATA_START);
    error = Wire.endTransmission();
    delay(5);
  }while(error);


  //move this to erase program
//  do
//  {
//    Wire.beginTransmission(chipAddress);
//    write16bit(DATA_PT_COUNT_ADDRESS);
//    write16bit(0x0000);
//    error = Wire.endTransmission();
//    delay(5);
//  }while(error);
}

int writeEEPROMData(uint16_t reading){
  
  uint16_t address = 0;
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  Wire.endTransmission();
  delay(5);
  
  Wire.requestFrom(CHIP_1,1);
  address |= Wire.read()<<8;
  
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS+1);
  Wire.endTransmission();
  delay(5);
  
  Wire.requestFrom(CHIP_1,1);
  address |= Wire.read();
  Serial.println(address);
  
  int i2cAddress;
  if(address < 0x1000){i2cAddress = CHIP_1;}
  else if(address < 0x2000){i2cAddress = CHIP_2;}
  else if(address < 0x3000){i2cAddress = CHIP_3;}
  else{i2cAddress = CHIP_4;}
  
  write16bit(address);
  Wire.beginTransmission(i2cAddress);
  write16bit(reading);
  Wire.endTransmission();
  delay(5);
  
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  write16bit(address+2);
  Wire.endTransmission();
  delay(5);
  
  uint16_t count = 0;
  Wire.beginTransmission(CHIP_1);
  write16bit(DATA_PT_COUNT_ADDRESS);
  Wire.endTransmission();
  delay(5);
  
  Wire.requestFrom(CHIP_1,1);
  count |= Wire.read()<<8;
  
  Wire.beginTransmission(CHIP_1);
  write16bit(DATA_PT_COUNT_ADDRESS+1);
  Wire.endTransmission();
  delay(5);
  
  Wire.requestFrom(CHIP_1,1);
  count |= Wire.read();
  
  count++;
  
  Wire.beginTransmission(CHIP_1);
  write16bit(DATA_PT_COUNT_ADDRESS);
  write16bit(count);
  Wire.endTransmission();
  delay(5);
}

void write16bit(uint16_t value){ //bigEndian
  Wire.write((value & HIGH_MASK)>>8);
  Wire.write(value & LOW_MASK);
}
