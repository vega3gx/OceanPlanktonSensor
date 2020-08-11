#define DAC_SIZE 10
#define LASER_MIN 240
#define LASER_MAX 512

#define TARGET 200

int DAC[DAC_SIZE] = {12, 11, 10, 9, 8, 7, 4, 5, 3, 2};
int brightness = LASER_MIN;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by
int ambient =0;
int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
// outside leads to ground and +5V

void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < DAC_SIZE; thisPin++) {
    pinMode(DAC[thisPin], OUTPUT);
  }
  Serial.begin(9600);           //  setup serial
  // declare pin 9 to be an output:
  DACSetValue(0);
  ambient = analogRead(analogPin);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  DACSetValue(brightness);
  int precept = analogRead(analogPin)-ambient;
  if(precept<TARGET){brightness++;}
  else if (precept>TARGET){brightness--;}
  char out[15];
  sprintf(out, "Laser brightness = %d Sensor Reads = %d", brightness,precept);
  Serial.println(out);
  Serial.println("**************************");
  delay(1);
}

void DACSetValue(uint16_t value){
  if(value>1023){value=1023;}
  uint16_t mask = 0x001;
  for(int i=0;i<DAC_SIZE;i++){
    digitalWrite(DAC[i],value & mask);
    mask = mask<<1;
  }
}
