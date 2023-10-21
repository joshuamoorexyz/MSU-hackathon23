/*
  Added variables to keep track of the motor's position
  added tested values for the time needed to close and open the blinds

*/

#include "uRTCLib.h"
#define in1 7 // define digital pin 7
#define in2 6 // define digital pin 6
int sensorPin = 0; // define analog pin 0
int value = 0;
int motorPosition = 0; // 0 = closed (default), 1 = open

uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600); // establish analog data output from Uno to PC 9600 baud rate
  pinMode(in1, OUTPUT); // tells pin Digital7 to act as an output
  pinMode(in2, OUTPUT); // tells pin Digital6 to act as an output

  URTCLIB_WIRE.begin();
}

void loop() {
  value = analogRead(sensorPin); // set the light level to value
  Serial.println(value, DEC); // print value so i know what value i'm receiving.
  Serial.println(motorPosition);
  delay(100); // 100ms wait between analog data

  rtc.refresh();
  Serial.print("Current Date & Time: ");
  Serial.print(rtc.year());
  Serial.print('/');
  Serial.print(rtc.month());
  Serial.print('/');
  Serial.print(rtc.day());

  Serial.print(" (");
  Serial.print(daysOfTheWeek[rtc.dayOfWeek()-1]);
  Serial.print(") ");

  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.print(rtc.minute());
  Serial.print(':');
  Serial.println(rtc.second());
    
  delay(1000);

// code for light controlled motor motion
 
  if (motorPosition == 0 && value < 100 && 6 <= rtc.hour()) { // value for motor to open blinds and check if it's closed and check if time is later than 6am
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(43000); // opening for 43sec
    motorPosition = 1;
  } else if (motorPosition == 1 && value > 600 && 19 <= rtc.hour()) { // value for motor to close blinds and check if it's open and check if time is later than 7pm
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(43000); // closing for 43sec
    motorPosition = 0;
  } else { // every other value when it's not on
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}