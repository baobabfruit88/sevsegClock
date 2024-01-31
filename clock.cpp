#include "SevSeg.h"
#include <iostream>
#include <string>

//Object for the display
SevSeg sevseg;

//We need to set some variables.
int hour;
int minute;
//Because we dont want the sccreen to refresh every second and only show one digit.
//We use the native fuction "millies" which is a counter of milliseconds since the arduino is powered.
//However it overflows after about 50 days so we work around that.
unsigned long previousMillis = 0;
unsigned long overflowCounter = 0;
//We need an update interval for the screen, one minute is enough.
const long interval = 60000; // Update every 1 minute
unsigned long startTime = 0;
const unsigned long ULONG_MAX = 0UL - 1UL;

void setup() {
  //These are all for the seven segment display hardware
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = true;
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  // Set the initial time here
  hour = 21;
  minute = 51;

  // Display the initial time
  int time = hour * 100 + minute;
  sevseg.setNumber(time);
  sevseg.refreshDisplay();

  //And here we set the initial values for time tracking 
  previousMillis = millis();
  startTime = millis() - (hour * 3600 + minute * 60) * 1000;
}

//All cpp projects on arduino run from this loop 
void loop(){
  settime();
  updateClock();
}

//We use this method to set the time on the display. 
void settime() {
  // Calculate total elapsed time considering program start, overflow, and reference time
  unsigned long elapsedTime = millis() - startTime + overflowCounter * ULONG_MAX;

  // Calculate hours and minutes
  unsigned long elapsedMinutes = elapsedTime / 60000;
  hour = (elapsedMinutes / 60) % 24;
  minute = elapsedMinutes % 60;

  int time = hour * 100 + minute;
  sevseg.setNumber(time);
  sevseg.refreshDisplay();
}

void updateClock() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update the time based on elapsed minutes
    hour = (hour + (minute + 1) / 60) % 24;
    minute = (minute + 1) % 60;

    // Call the function to update the display
    settime();
  }

  // Handle 50 day overflow
  if (currentMillis < previousMillis) {
    overflowCounter++;
    startTime = currentMillis;
  }
}