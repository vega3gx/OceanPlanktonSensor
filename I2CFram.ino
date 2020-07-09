#include <Wire.h>
//#include <Serial.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  //Wire.setClock(10000);
  Serial.begin(9600);
  
  int error =1;
  while(error){
    Wire.beginTransmission(0x50); //0xA0 is device write address
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0x98);
    error =Wire.endTransmission();
    Serial.println(error);
    delay(1);
  }
}

uint8_t reading = 0;

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Begin");
  Wire.beginTransmission(0x50); //0xA0 is device write address
  Wire.write(0x00);
  Wire.write(0x00);
  Serial.println(Wire.endTransmission());

  delay(1);

  Wire.requestFrom(0x50,1);
  //if(1<=Wire.available()){
    reading = Wire.read();
    Serial.println(reading);
  //}else{Serial.println("Data not availible");}
  delay(1);
}
