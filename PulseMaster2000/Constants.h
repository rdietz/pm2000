#ifndef CONST_H
#define CONST_H

// Set up for PM2000 UNO board

// Version
#define VERSION "PM2000-UNO-Ver-1.4-Encoder"

const static float MINIMUM_DISTANCE = 1.0;        // Minimum distance in metres between trees

const static float CALIBRATE_SPEED_INIT = 1.0;   // Simulated tractor speed in km/hr for simulation mode

const static int OPERATE = 1;
const static int CALMODE = 2;
const static int CALRUN = 3;

const static int CALDISTANCE = 10;  // Metres for calibration run

// EEPROM addresses - allow two bytes per int
const static  int AddrFlag = 0;
const static  int AddrPulses = 2;
const static  int AddrRelay1Time = 4;
const static  int AddrRelay1Delay = 6;
const static  int AddrRelay2Time = 8;
const static  int AddrRelay2Delay = 10;

// Arduino I/O Parameters
const static int gpsInterrupt = 0;  // Interrupt 0 = pin 2
const static int ledPin1 = 3;
const static int ledPin2 = 4;
const static int relay1Pin = 5;
const static int relay2Pin = 6;
const static int buttonPin = 7;

// thumbwheel connections
const static int thumb1Pin = 11;
const static int thumb2Pin = 10;
const static int thumb4Pin = 9;
const static int thumb8Pin = 8;
const static int thumbDigit1Pin = 12;  // Units
const static int thumbDigit2Pin = 13;  // Tenths
const static int thumbDigit3Pin = A0;  // Hundredths



#endif	// CONST_H
