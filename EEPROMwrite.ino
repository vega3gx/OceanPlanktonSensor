#include <Wire.h>
void setup() {
  char output[15];
  Wire.begin();
  Serial.begin(9600);
  for(uint16_t address = 0; address<=0xFFF; address++){
    int error =3;
    while(error){
      Wire.beginTransmission(0x50);
      Wire.write((address&0xF00)>>8);
      Wire.write(address&0x0FF);
      Wire.write((address&0x0FF)+1);
      error = Wire.endTransmission();
      //delay(1);
    }

//    Wire.requestFrom(0x50,1);
//    int reading = Wire.read();
//    sprintf(output,"%03x  %02x",address,reading);
//    Serial.println(output);
  }
  Serial.println("done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
