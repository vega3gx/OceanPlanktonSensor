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
#define LOCAL_CHIP_MASK 0x0FFF

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Logging Begin");
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
    writeEEPROMData(0x0000);

    Wire.beginTransmission(CHIP_1);
    write16bit(STACK_PTR_ADDRESS+1);
    Wire.endTransmission();
    
    Wire.requestFrom(CHIP_1,1);
    int add = Wire.read();
    Serial.println(add);
    delay(2000);
}


int writeEEPROMData(uint16_t reading){

  //Set EEPROM ptr to stack pointer address location
  uint16_t address = 0; //address of next free memory location
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  Wire.endTransmission();
  delay(5);

  //get address high byte
  Wire.requestFrom(CHIP_1,1);
  address |= Wire.read()<<8;

  //set stack pointer to location of low byte address
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS+1);
  Wire.endTransmission();
  delay(5);

  //get address low byte
  Wire.requestFrom(CHIP_1,1);
  address |= Wire.read();
  //Serial.print(address);

  // find chip
  int i2cAddress;
  if(address < 0x1000){i2cAddress = CHIP_1;}
  else if(address < 0x2000){i2cAddress = CHIP_2;}
  else if(address < 0x3000){i2cAddress = CHIP_3;}
  else{i2cAddress = CHIP_4;}

  //write recorded data
  Wire.beginTransmission(i2cAddress);
  write16bit(address & LOCAL_CHIP_MASK);
  write16bit(reading);
  Wire.endTransmission();
  delay(5);
  //Serial.print( reading);
  //Serial.println(" ");

  //increment next free address pointer by 2
  Wire.beginTransmission(CHIP_1);
  write16bit(STACK_PTR_ADDRESS);
  write16bit(address+2);
  Wire.endTransmission();
  delay(5);

  //get number of readings
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
