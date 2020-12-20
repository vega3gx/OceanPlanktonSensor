#define DAC_SIZE 10
#define LASER_MIN 240
#define LASER_MAX 512

//int DAC[DAC_SIZE] = {12, 11, 10, 9, 8, 7, 4, 5, 3, 2};
int brightness = LASER_MIN;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
// outside leads to ground and +5V
int val = 0;  // variable to store the value read

void setup() {
//  for (int thisPin = 0; thisPin < DAC_SIZE; thisPin++) {
//    pinMode(DAC[thisPin], OUTPUT);
//  }
  Serial.begin(9600);           //  setup serial
  // declare pin 9 to be an output:
}

void loop() {
  char output[15];
  // set the brightness of pin 9:
  DACSetValue(brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= LASER_MIN || brightness >= LASER_MAX) {
    fadeAmount = -fadeAmount;
  }
  val = analogRead(analogPin);  // read the input pin
  sprintf(output, "%d,%d", brightness, val);
  Serial.println(output);          // debug value
  delay(30);
}

void DACSetValue(uint16_t value){
  if(value>1023){value=1023;}
  uint16_t mask = 0x001;
  for(int i=0;i<DAC_SIZE;i++){
    //digitalWrite(DAC[i],value & mask);
    mask = mask<<1;
  }
}
