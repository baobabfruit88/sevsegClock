# Arduino 7-Segment Display Clock

This Arduino project is designed to create a simple clock using a 7-segment display. It's a great learning exercise for utilizing Arduino to create time-based projects.

## Hardware Requirements

- Arduino Board
- 7-Segment Display
- Resistors
- Jumper Wires

## Libraries Used

- [SevSeg Library](https://github.com/DeanIsMe/SevSeg): This library simplifies the process of working with 7-segment displays on Arduino.

## Getting Started

1. Clone or download this repository.
2. Install the SevSeg library in your Arduino IDE.
3. Connect the 7-segment display to your Arduino following the wiring instructions in the image. the 1k ohm is simply to indicate you need to use 4*250 ohm.
4. Upload the provided Arduino sketch to your board.

## Code Overview

The Arduino sketch utilizes the SevSeg library to control the 7-segment display. The main functionalities include updating the time every minute and handling overflow for long-term tracking.

```cpp
// Calculate total elapsed time considering program start, overflow, and reference time
unsigned long elapsedTime = millis() - startTime + overflowCounter * ULONG_MAX;

// Set the initial time directly
hour = 21;
minute = 45;

// Update the time based on elapsed minutes
hour = (hour + (minute + 1) / 60) % 24;
minute = (minute + 1) % 60;
