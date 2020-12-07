/*
  Simple RTC Alarm for Arduino Zero and MKR1000

  Demonstrates how to set an RTC alarm for the Arduino Zero and MKR1000

  This example code is in the public domain

  http://arduino.cc/en/Tutorial/SimpleRTCAlarm

  created by Arturo Guadalupi <a.guadalupi@arduino.cc>
  25 Sept 2015
  
  modified
  21 Oct 2015
*/
#include <SPI.h>
#include <SD.h>
#include "RTCZero.h"
File myFile;

#define NAME "bathtub5.txt"

int analogPin = A1; // potentiometer wiper (middle terminal) connected to analog pin 3
// outside leads to ground and +5V
int val = 0;  // variable to store the value read


/* Create an rtc object */
RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 30;
const byte hours = 18;

/* Change these values to set the current initial date */
const byte day = 6;
const byte month = 12;
const byte year = 20;
int minute = 31;
char output[15];

int laser = A0;


void setup()
{

  pinMode(laser,OUTPUT);
  analogWrite(laser,255);

  Serial.begin(9600);
    Serial.print("Initializing SD card...");

  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(NAME, FILE_WRITE);

  rtc.begin(); // initialize RTC 24H format

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmTime(18, minute, 00);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  
  rtc.attachInterrupt(alarmMatch);
}

void loop()
{

}

void alarmMatch()
{
  myFile = SD.open(NAME, FILE_WRITE);
  val = analogRead(analogPin);  // read the input pin
  sprintf(output, "%d,%d,%d,%d ", val,rtc.getHours(),rtc.getMinutes(),rtc.getSeconds());
  Serial.println("Measurement");
  Serial.println(output);
  minute = minute+1;
  rtc.setAlarmTime(18,minute, 00);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  myFile.println(output);
  myFile.close();
}
