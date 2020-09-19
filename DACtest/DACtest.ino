#define DAC_SIZE 10
#define LASER_MIN 240
#define LASER_MAX 512

int DAC[DAC_SIZE] = {12,11,10,9,8,7,4,5,3,2};
int brightness = LASER_MIN;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by


void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < DAC_SIZE; thisPin++) {
    pinMode(DAC[thisPin], OUTPUT);
  }
  //DACSetValue(1023);
Serial.begin(9600);
//DACSetValue(256);
pinMode (2,OUTPUT);
digitalWrite(2,1);
//digitalWrite(12,1);


}

uint16_t DAClevel =0;

void loop() {
//  // put your main code here, to run repeatedly:
//    DACSetValue(brightness);
//
//  // change the brightness for next time through the loop:
//  brightness = brightness + fadeAmount;
//
//  // reverse the direction of the fading at the ends of the fade:
//  if (brightness <= LASER_MIN || brightness >= LASER_MAX) {
//    fadeAmount = -fadeAmount;
//  }
//  // wait for 30 milliseconds to see the dimming effect
//  Serial.println(brightness);
//  delay(100);
}

void DACSetValue(uint16_t value){
  if(value>1023){value=1023;}
  uint16_t mask = 0x001;
  for(int i=0;i<DAC_SIZE;i++){
    digitalWrite(DAC[i],value & mask);
    Serial.println(mask);
    Serial.println(value & mask);
    mask = mask<<1;
  }
  
}
