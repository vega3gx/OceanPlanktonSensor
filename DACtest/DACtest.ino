#define DAC_SIZE 8

int DAC[8] = {12,11,10,9,8,7,4,5};
int brightness = 60;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by


void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < DAC_SIZE; thisPin++) {
    pinMode(DAC[thisPin], OUTPUT);
  }
}

uint8_t DAClevel =0;

void loop() {
  // put your main code here, to run repeatedly:
    DACSetValue(brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 60 || brightness >= 128) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(100);
}

void DACSetValue(uint8_t value){
  uint8_t mask = 0x01;
  for(int i=0;i<8;i++){
    digitalWrite(DAC[i],value & mask);
    mask = mask<<1;
  }
}
