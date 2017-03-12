#ifndef CONST_H
#define CONST_H

// Set up for PM2000 UNO board

// Version
#define VERSION "PM2000-UNO-V3"

const static float MINIMUM_DISTANCE = 1.0;        // Minimum distance in metres between trees

const static float CALIBRATE_SPEED_INIT = 2.5;   // Simulated tractor speed in km/hr for simulation mode

const static int OPERATE = 1;
const static int CALMODE = 2;
const static int CALRUN = 3;


// EEPROM addresses - allow two bytes per int
const static  int AddrFlag = 10;
const static  int AddrPulses = 20;
const static  int AddrRelay1Time = 30;
const static  int AddrRelay1Delay = 40;
const static  int AddrRelay2Time = 50;
const static  int AddrRelay2Delay = 60;
const static  int AddrRelay3Time = 80;
const static  int AddrRelay3Delay = 100;
const static  int AddrRelay4Time = 120;
const static  int AddrRelay4Delay = 140;

// Arduino I/O Parameters
const static int interruptPin = 2;   // Interrupt (0) on pin 2
const static int ledPin1 = 4;        // Red LED +, Green LED -
const static int ledPin2 = 3;        // Red LED -, Green LED +
const static int relay1Pin = A4;
const static int relay2Pin = 12;
const static int relay3Pin = 11;
const static int relay4Pin = 10;
const static int buttonPin = A3;
const static int limitswitchPin = A5;

// thumbwheel connections
const static int thumb1Pin = 5;
const static int thumb2Pin = 6;
const static int thumb4Pin = 7;
const static int thumb8Pin = 8;
const static int thumbDigit1Pin = A2;  // Metres
const static int thumbDigit2Pin = A1;  // Tenths
const static int thumbDigit3Pin = A0;  // Hundredths



#endif	// CONST_H
