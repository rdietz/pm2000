#ifndef CONST_H
#define CONST_H

// Set up for PM2000 UNO board

// Version
#define VERSION "PM2000-UNO-Ver-1.1"

// Operational Parameters
const static int RELAY1_DELAY = 0;
const static int RELAY1_PULSE_TIME = 500;

const static int RELAY2_DELAY = 500;
const static int RELAY2_PULSE_TIME = 500;

const static float GPS_PULSES_PER_METRE = 76.14;
const static float MINIMUM_DISTANCE = 1.0;        // Minimum distance in metres between trees

const static float CALIBRATE_MODE_INIT = false;
const static float CALIBRATE_SPEED_INIT = 1.0;   // Simulated tractor speed in km/hr for calibration mode

// Arduino I/O Parameters
const static int gpsInterrupt = 0;  // Interrupt 0 = pin 2
const static int ledPin1 = 3;
const static int ledPin2 = 4;
const static int relay1Pin = 5;
const static int relay2Pin = 6;
const static int buttonPin = 7;

// thumbwheel connections
const static int thumb1Pin = 8;
const static int thumb2Pin = 9;
const static int thumb4Pin = 10;
const static int thumb8Pin = 11;
const static int thumbDigit1Pin = 12;  // Units
const static int thumbDigit2Pin = 13;  // Tenths


#endif	// CONST_H
