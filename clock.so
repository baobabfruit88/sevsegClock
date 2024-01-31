#include "SevSeg.h"
#include <iostream>
#include <string>

SevSeg sevseg;
//Set your starting time manually
  int hour = 21;
  int minute = 20;
  unsigned long previousMillis = 0;
const long interval = 60000; // Update every 1 second

void setup(){
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = true;
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
  settime();
  updateClock();
}

void settime() {
  int time = hour * 100 + minute;
  sevseg.setNumber(time);
  sevseg.refreshDisplay();
}

void updateClock() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update the time based on elapsed seconds
    minute++;
    if (minute == 60) {
      minute = 0;
      hour++;
      if (hour == 24) {
        hour = 0;
      }
    }

    // Call the function to update the display
    settime();
  }
}
