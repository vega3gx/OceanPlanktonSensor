/*

  Sleep RTC Alarm for Arduino Zero

  Demonstrates the use an alarm to wake up an Arduino zero from Standby mode

  This example code is in the public domain

  http://arduino.cc/en/Tutorial/SleepRTCAlarm

  created by Arturo Guadalupi

  17 Nov 2015

  modified

  01 Mar 2016



  NOTE:

  If you use this sketch with a MKR1000 you will see no output on the serial monitor.

  This happens because the USB clock is stopped so it the USB connection is stopped too.

  **To see again the USB port you have to double tap on the reset button!**

*/

#include "RTCZero.h"

/* Create an rtc object */

RTCZero rtc;

/* Change these values to set the current initial time */

const byte seconds = 0;

const byte minutes = 00;

const byte hours = 17;

/* Change these values to set the current initial date */

const byte day = 17;

const byte month = 11;

const byte year = 15;

byte minute =0;

int strength =128;


void setup()
{

  Serial.begin(9600);
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, OUTPUT);

  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);

  rtc.begin();

  rtc.setTime(hours, minute, seconds);

  rtc.setDate(day, month, year);

  rtc.setAlarmTime(17, 00, 10);

  rtc.enableAlarm(rtc.MATCH_HHMMSS);

  rtc.attachInterrupt(alarmMatch);

  rtc.standbyMode();
}

void loop()
{
  //rtc.standbyMode();    // Sleep until next alarm match
}

void alarmMatch()
{

  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  analogWrite(A0, 255);
  
  //rtc.setAlarmTime(17, minute, 0);

  //rtc.standbyMode();
}
